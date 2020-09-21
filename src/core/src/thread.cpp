//------------------------------------------------------------------------------
//       Copyright 2014-2018 Creepy Doll Games LLC. All rights reserved.
//
//                  The best method for accelerating a computer
//                     is the one that boosts it by 9.8 m/s2.
//------------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
// NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//------------------------------------------------------------------------------

#if e_compiling( web )
  #include<pthread.h>
  #include<sched.h>
#elif e_compiling( microsoft )
  #define WIN32_LEAN_AND_MEAN
  #define NOMINMAX
  #include<windows.h>
#elif e_compiling( android )
  #include<signal.h>
  #include<unistd.h>
#elif e_compiling( linux )
  #include<sys/syscall.h>
#elif e_compiling( osx )||e_compiling( ios )
  #include<pthread.h>
  #include<sched.h>
#endif

using namespace EON;
using namespace gfc;

//================================================|=============================
//Thread:{                                        |
  //Global:{                                      |

    void e_backoff( const double start ){
      #if !e_compiling( microsoft )
        const double now = e_seconds();
        const double dur = now - start;
        if( dur > .20 ){
          Thread::sleep( 2 );
          return;
        }
        if( dur > .10 ){
          Thread::sleep( 1 );
          return;
        }
        if( dur > .01 ){
          Thread::yield();
          return;
        }
      #endif
    }

  //}:                                            |
  //Private:{                                     |
    //makeUid:{                                   |

      namespace{
        u32              __masters = Thread::tid();
        __thread Thread* __context = nullptr;
        std::atomic<s32> __count{};
        std::atomic<s32> __peak{};
        bitbucket<65536> __masks;
        u32 makeUid(){
          return u32(__masks.set() & 0xFFFFFFFF );
        }
        std::unordered_map<u32,Thread*>& getThreadMap(){
          static std::unordered_map<u32,Thread*>_map;
          return _map;
        }
        std::mutex& getGlobalLock(){
          static std::mutex _mutex;
          return _mutex;
        }
      }

    //}:                                          |
  //}:                                            |
  //Methods:{                                     |
    //RedWorker:{                                 |

      void Thread::RedWorker( Thread* pThread ){
        if( !pThread ){
          e_unreachable( "Thread pointer is nil!" );
        }

        //----------------------------------------------------------------------
        // Hook thread into database.
        //----------------------------------------------------------------------

        // Grab the platform thread identifier.
        const u32 tid = Thread::tid();

        // Save off a pointer to incoming thread.
        pThread->toFlags()->bStarted = 1;
        pThread->setTID( tid );
        __context = pThread;

        // Add thread to the database.
        { __peak = e_max<s32>(__peak, ++__count );
          std::lock_guard l( getGlobalLock() );
          getThreadMap()[ tid ] = pThread;
        }

        //----------------------------------------------------------------------
        // Execute lambda and/or run method.
        //----------------------------------------------------------------------

        #if e_compiling( osx )
          { char text[ 33 ];// Don't use e_xfs here, it blocks other threads.
            sprintf( text, "RedWorker: %u", tid );
            pthread_setname_np( text );
          }
        #elif e_compiling( microsoft )
          SetThreadDescription( GetCurrentThread(), L"RedWorker" );
        #endif
        if( pThread->m_onLambda ){
            pThread->m_onLambda();
        }
        pThread->run();

        //----------------------------------------------------------------------
        // Detach from threading database.
        //----------------------------------------------------------------------

        { std::lock_guard l( getGlobalLock() );
          getThreadMap().erase( tid );
          --__count;
        }
        pThread->toFlags()->bIsDead = 1;
      }

    //}:                                          |
    //isCurrent:{                                 |

      bool Thread::isCurrent()const{
        return( tid()==m_uTID );
      }

    //}:                                          |
    //foreach:{                                   |

      void Thread::foreach( const std::function<void( const IThread* )>& lambda ){
        std::lock_guard l( getGlobalLock() );
        for( auto t:getThreadMap() ){
          lambda( t.second );
        }
      }

    //}:                                          |
    //acquire:{                                   |

      bool Thread::acquire(){
        //acquire() must succeed: start thread if it hasn't been already.
        if( !m_pThread ){
          start();
          yield();
        }
        //block until signaled or in other words join the thread.
        if( !isCurrent() ){
          try{
            m_pThread->join();
          }
          catch(...){
          }
          return true;
        }
        return false;
      }

    //}:                                          |
    //release:{                                   |

      void Thread::release(){
        // Do not start in acquire if not already started.
        if( m_pThread ){
          if( !m_tFlags->bIsDead ){
            // Kill the thread at next convenience.
            m_tFlags->bIsDying = 1;
            // Block until thread dies (returns).
            if( acquire() ){
              // This pointer has been deleted in acquire.
              m_pThread = nullptr;
            }
          }
        }else{
          m_tFlags->bIsDead = 1;
        }
      }

    //}:                                          |
    //context:{                                   |

      Thread& Thread::context(){
        if( !__context ){
          static Thread main;
          __context = &main;
        }
        return *__context;
      }

    //}:                                          |
    //exists:{                                    |

      bool Thread::exists( const u32 tid ){
        bool bResult =( tid == __masters );
        if( !bResult ){
          std::lock_guard l( getGlobalLock() );
          for( auto t:getThreadMap() ){
            if( t.second->isTID( tid )){
              bResult = true;
              break;
            }
          }
        }
        return bResult;
      }

    //}:                                          |
    //yield:{                                     |

      void Thread::yield(){
        std::this_thread::yield();
      }

    //}:                                          |
    //sleep:{                                     |

      void Thread::sleep( const s32 ms ){
        std::this_thread::sleep_for( std::chrono::milliseconds( ms ));
      }

    //}:                                          |
    //start:{                                     |

      void Thread::start(){
        if( !m_pThread ){
          m_pThread = new std::thread( RedWorker, this );
        }
      }

    //}:                                          |
    //count:{                                     |

      s32 Thread::count(){
        return __count;
      }

    //}:                                          |
    //alive:{                                     |

      bool Thread::alive()const{
        for(;;){
          // If the thread is dying return false.
          if( m_tFlags->bIsDying ){
            return false;
          }
          // If the thread is dead return false.
          if( m_tFlags->bIsDead ){
            return false;
          }
          // If thread hasn't started then return false.
          if( !m_pThread ){
            return false;
          }
          // We cannot pause the main thread!
          if( !IEngine::isMainThread() && m_tFlags->bPaused ){
            sleep( 10 );
            continue;
          }
          // Reset scratch memory buffer.
          e_sreset();
          // Thread is still alive!
          return true;
        }
      }

    //}:                                          |
    //peak:{                                      |

      s32 Thread::peak(){
        return __peak;
      }

    //}:                                          |
    //uid:{                                       |

      u32 Thread::uid(){
        if( __context ){
          return __context->m_uUID;
        }
        return 0;
      }

    //}:                                          |
    //tid:{                                       |

      u32 Thread::tid(){
        u32 tidResult = 0;
        #if e_compiling( web )
          static __thread u32 tid = 1;
          tidResult = tid++;
        #elif e_compiling( microsoft )
          tidResult = GetCurrentThreadId();
        #elif e_compiling( android )
          tidResult = u32( gettid() );
        #elif e_compiling( ios )||e_compiling( osx )
          tidResult = u32( pthread_mach_thread_np( pthread_self() ));
        #elif e_compiling( linux )
          #ifdef SYS_gettid
            tidResult = u32( syscall( SYS_gettid ));
          #endif
        #else
          pthread_id_np_t curId;
          pthread_getunique_np( &pthread_self(), &curId );
          tidResult = u32( curId );
        #endif
        return tidResult;
      }

    //}:                                          |
  //}:                                            |
  //Ctor:{                                        |

    Thread::Thread( Thread&& rvalue     )
        : m_pPayload( rvalue.m_pPayload )
        , m_pThread(  rvalue.m_pThread  )
        , m_uTID(     rvalue.m_uTID     )
        , m_uUID(     rvalue.m_uUID     )
        , m_tFlags(   rvalue.m_tFlags   ){
      rvalue.m_pPayload    = nullptr;
      rvalue.m_pThread     = nullptr;
      rvalue.m_tFlags.all  = 0;
      rvalue.m_uUID        = 0;
      rvalue.m_uTID        = 0;
    }

    Thread::Thread( const Lambda& lambda )
      : m_onLambda( lambda )
    {}

    Thread::Thread( std::thread* pThread )
        : m_pPayload( nullptr )
        , m_pThread( pThread )
        , m_uTID( tid() )
        , m_uUID( makeUid() ){
      m_tFlags->bCurrent = 1;
    }

    Thread::Thread( const Thread& thread )
        : m_uUID( makeUid() ){
      *this = thread;
    }

    Thread::Thread()
      : m_uUID( makeUid() )
    {}

  //}:                                            |
  //Dtor:{                                        |

    Thread::~Thread(){
      __masks.reset( m_uUID );
      release();
      m_onLambda = nullptr;
    }

  //}:                                            |
//}:                                              |
//================================================|=============================
