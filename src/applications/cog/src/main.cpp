//------------------------------------------------------------------------------
//                    Copyright 2022 Creepy Doll Software LLC.
//                            All rights reserved.
//
//                  The best method for accelerating a computer
//                     is the one that boosts it by 9.8 m/s2.
//------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//------------------------------------------------------------------------------

#include"luacore.h"
#include"ws.h"

using namespace EON;
using namespace gfc;
using namespace fs;

//------------------------------------------------|-----------------------------
//Actions:{                                       |
  //onUnpackage:{                                 |

    #if 0
      namespace{
        void onUnpackage( const string& path ){
          e_unpackage( path );
        }
      }
    #endif

  //}:                                            |
  //onPackage:{                                   |

    #if 0
      namespace{
        void onPackage( strings::const_iterator& it, const string& pkgName ){
          strings filesAndDirs;
          while( it ){
            filesAndDirs += *it;
            ++it;
          }
          e_package(
              filesAndDirs
            , pkgName
          );
        }
      }
    #endif

  //}:                                            |
//}:                                              |
//Private:{                                       |
  //[workspace]:{                                 |

    namespace{
      constexpr ccp kWorkspace = "workspace=class'workspace'{\n"
        //----------------------------------------|-----------------------------
        //new:{                                   |
          "  new=function(self,name)\n"
          "    return class'workspace'{\n"
          "      m_tProjects={},\n"
          "      m_sName=name,\n"
          "      new=function(self,label)\n"
          "        local t=class'project'{\n"
          //--------------------------------------|-----------------------------
          //Microsoft:{                           |
          "          dependencies=function(self,dependsOn)\n"
          "            self.m_dependencies=dependsOn\n"
          "          end,\n"
          "          winsdk=function(self,version)\n"
          "            self.m_winsdk=version\n"
          "            return self\n"
          "          end,\n"
          "          toolchain=function(self,version)\n"
          "            self.m_toolchain=version\n"
          "            return self\n"
          "          end,\n"
          //Creates a .def file for resources in a DLL.
          "          def=function(self,path)\n"
          "            self.m_def=path\n"
          "            return self\n"
          "          end,\n"
          //}:                                    |
          //Common:{                              |
            //set_include_paths:{                 |
            //TODO: Check this doesn't double up files like find_includes did.
            "          set_include_paths=function(self,paths)\n"
            "            if nil~=self.m_includePaths then\n"
            "              self.m_includePaths=self.m_includePaths..','..paths\n"
            "            else\n"
            "              self.m_includePaths=paths\n"
            "            end\n"
            "            return self\n"
            "          end,\n"
            //}:                                  |
            //find_resources:{                    |
            //TODO: Check this doesn't double up files like find_includes did.
            "          find_resources=function(self,paths)\n"
            "            if nil~=self.m_resPaths then\n"
            "              self.m_resPaths=self.m_resPaths..','..paths\n"
            "            else\n"
            "              self.m_resPaths=paths\n"
            "            end\n"
            "            return self\n"
            "          end,\n"
            //}:                                  |
            //find_libraries:{                    |
            "          find_libraries=function(self,paths)\n"
            "            if nil~=self.m_libraryPaths then\n"
            "              self.m_libraryPaths=self.m_libraryPaths..','..paths\n"
            "            else\n"
            "              self.m_libraryPaths=paths\n"
            "            end\n"
            "            return self\n"
            "          end,\n"
            //}:                                  |
            //find_sources:{                      |
            "          find_sources=function(self,paths)\n"
            "            if nil~=self.m_srcPaths then\n"
            "              self.m_srcPaths=self.m_srcPaths..','..paths\n"
            "            else\n"
            "              self.m_srcPaths=paths\n"
            "            end\n"
            "            return self\n"
            "          end,\n"
            //}:                                  |
            //skip_unity:{                        |
            "          skip_unity=function(self,files)\n"
            "            self.m_skipUnity=files\n"
            "            return self\n"
            "          end,\n"
            //}:                                  |
            //link_with:{                         |
            "          link_with=function(self,libs)\n"
            "            if type(libs)=='table'then\n"
            "              self.m_linkWith=libs\n"
            "            elseif type(libs)=='string'then\n"
            "              self.m_linkWith=libs\n"
            "            end\n"
            "            return self\n"
            "          end,\n"
            //}:                                  |
            //install:{                           |
            "          install=function(self,script)\n"
            "            self.m_installScript=script\n"
            "            return self\n"
            "          end,\n"
            //}:                                  |
            //defines:{                           |
            //         Usage: defines{...,...} or defines( debug, release )
            "          defines=function(self,t,r)\n"
            //           Process the debug build defines first.
            "            if type(t)=='table'then\n"
            "              if nil~=self.m_definesDbg then\n"
            "                self.m_definesDbg=self.m_definesDbg..','..t[1]\n"
            "              else\n"
            "                self.m_definesDbg=tostring(t[1])\n"
            "              end if nil~=self.m_definesRel then\n"
            "                self.m_definesRel=self.m_definesRel..','..t[2]\n"
            "              else\n"
            "                self.m_definesRel=t[2]\n"
            "              end\n"
            "            elseif type(t)=='string'then\n"
            "              if nil~=self.m_definesDbg then\n"
            "                self.m_definesDbg=self.m_definesDbg..','..t\n"
            "              else\n"
            "                self.m_definesDbg=t\n"
            "              end\n"
            "            elseif nil~=self.m_definesDbg then\n"
            "              self.m_definesDbg=self.m_definesDbg..','..t\n"
            "            else\n"
            "              self.m_definesDbg=tostring(t)\n"
            "            end\n"
            //           Process the release build defines next.
            "            if nil~=r then\n"
            "              if type(r)=='string'then\n"
            "                if nil~=self.m_definesRel then\n"
            "                  self.m_definesRel=self.m_definesRel..','..r\n"
            "                else\n"
            "                  self.m_definesRel=r\n"
            "                end\n"
            "              elseif nil~=self.m_definesRel then\n"
            "                self.m_definesRel=self.m_definesRel..','..r\n"
            "              else\n"
            "                self.m_definesRel=r\n"
            "              end\n"
            "            end\n"
            //           Return the self reference to caller so we can continue chaining.
            "            return self\n"
            "          end,\n"
            //}:                                  |
            //disable:{                           |
            "          disable=function(self, options)\n"
            "            self.m_disableOpts=options\n"
            "            return self\n"
            "          end,\n"
            //}:                                  |
            //target:{                            |
            "          target=function(self,build)\n"
            "            self.m_build=build\n"
            "            return self\n"
            "          end,\n"
            //}:                                  |
            //prefix:{                            |
            "          prefix=function(self,header)\n"
            "            self.m_prefixHeader=header\n"
            "            return self\n"
            "          end,\n"
            //}:                                  |
            //ignore:{                            |
            "          ignore=function(self,regexes)\n"
            "            if nil~=self.m_ignore then\n"
            "              self.m_ignore=self.m_ignore..','..regexes\n"
            "            else\n"
            "              self.m_ignore=regexes\n"
            "            end\n"
            "            return self\n"
            "          end,\n"
            //}:                                  |
            //c_lang:{                            |
            //This is a shortcut function; for brevity (or not).
            "          c_lang=function(self,lang)\n"
            "            self.m_clanguage=lang\n"
            "            return self\n"
            "          end,\n"
            "          c_language=function(self,l)\n"
            "            return self:c_lang( l )\n"
            "          end,\n"
            //This is a shortcut function; for brevity (or not).
            "          lang=function(self,lang)\n"
            "            self.m_language=lang\n"
            "            return self\n"
            "          end,\n"
            "          language=function(self,l)\n"
            "            return self:lang( l )\n"
            "          end,\n"
            //}:                                  |
            //unity:{                             |
            "          unity=function(self,enable)\n"
            "            self.m_bUnity=enable\n"
            "          end,\n"
            //}:                                  |
            //libs:{                              |
            "          libs=function(self,paths)\n"
            "            if nil~=self.m_resPaths then\n"
            "              self.m_libs=self.m_libs..','..paths\n"
            "            else\n"
            "              self.m_libs=paths\n"
            "            end\n"
            "            return self\n"
            "          end,\n"
            //}:                                  |
          //}:                                    |
          //Apple:{                               |
          "          disableLibraryValidation=function(self,disable)\n"
          "            self.m_disableLibValidation=disable\n"
          "            return self\n"
          "          end,\n"
          "          appleSilicon=function(self, enable)\n"
          "            self.m_enableAppleSilicon=enable\n"
          "            return self\n"
          "          end,\n"
          "          universal=function(self, enable)\n"
          "            self.m_enableUniversal=enable\n"
          "            return self\n"
          "          end,\n"
          "          not_embedded=function(self)\n"
          "            self.m_noEmbedAndSign=true\n"
          "            return self\n"
          "          end,\n"
          "          embed_and_sign=function(self,files)\n"
          "            self.m_filesToEmbedAndSign=files\n"
          "            return self\n"
          "          end,\n"
          "          load_all_symbols=function(self,enable)\n"
          "            self.m_loadAllSymbols=enable\n"
          "            return self\n"
          "          end,\n"
          "          harden=function(self,hardenedRuntime)\n"
          "            self.m_hardenedRuntime=hardenedRuntime\n"
          "            return self\n"
          "          end,\n"
          "          deployment=function(self,version)\n"
          "            self.m_deployTo=version\n"
          "            return self\n"
          "          end,\n"
          "          sdk_version=function(self,version)\n"
          "            self.m_sdkVersion=version\n"
          "            return self\n"
          "          end,\n"
          "          enableARC=function(self,enable)\n"
          "            self.m_arcEnabled=enable\n"
          "            return self\n"
          "          end,\n"
          "          export_headers=function(self,dirsAndFiles)\n"
          "            self.m_exportHeaders=dirsAndFiles\n"
          "            return self\n"
          "          end,\n"
          "          export_refs=function(self,dirsAndFiles)\n"
          "            self.m_exportRefs=dirsAndFiles\n"
          "            return self\n"
          "          end,\n"
          "          organization=function(self,name)\n"
          "            self.m_orgName=name\n"
          "            return self\n"
          "          end,\n"
          "          identifier=function(self,id)\n"
          "            self.m_bundleId=id\n"
          "            return self\n"
          "          end,\n"
          "          team=function(self,name)\n"
          "            self.m_teamName=name\n"
          "            return self\n"
          "          end,\n"
          "          find_frameworks=function(self,paths)\n"
          "            self.m_frameworkPaths=paths\n"
          "            return self\n"
          "          end,\n"
          "          os_target=function(self,osTarget)\n"
          "            self.m_osTarget=osTarget\n"
          "            return self\n"
          "          end,\n"
          //}:                                    |
          //--------------------------------------|-----------------------------
          "        }\n"
          "        self.m_tProjects[label]=t\n"
          "        t.label=label\n"
          "        return t\n"
          "      end,\n"
          "    }\n"
          "  end,\n"

        //}:                                      |
        //----------------------------------------|-----------------------------
      "}\n";
    }

  //}:                                            |
  //[platform]:{                                  |

    namespace{

      //------------------------------------------------------------------------
      // Get the platform name; for the user to query the build name.
      //------------------------------------------------------------------------

      string getPlatformName(){
        if( Workspace::bmp->bEmscripten ){
          return"  return'wasm'";
        }
        if( Workspace::bmp->bQmake ){
          return"  return'qmake'";
        }
        if( Workspace::bmp->bXcode11 ||
            Workspace::bmp->bXcode12 ||
            Workspace::bmp->bXcode14 ){
          return"  return'macos'";
        }
        if( Workspace::bmp->bVS2019 ||
            Workspace::bmp->bVS2022 ){
          return"  return'win64'";
        }
        if( Workspace::bmp->bNinja ){
          return"  return'linux'";
        }
        if( Workspace::bmp->bNDK ){
          return"  return'android'";
        }
        return nullptr;
      }

      //------------------------------------------------------------------------
      // Get the platform class; for the user to query the platform.
      //------------------------------------------------------------------------

      string platformClass(){
        string out;
        out << "platform=class'platform'{\n";

        //----------------------------------------|-----------------------------
        //builds:{                                |

          out << "builds=function()\n";
          out << "  return{ getBuildSystems() }\n";
          out << "end,\n";

        //}:                                      |
        //vendor:{                                |

          out << "vendor = function()\n";
          if( Workspace::bmp->bXcode11 ||
              Workspace::bmp->bXcode12 ||
              Workspace::bmp->bXcode14 ){
            out << "  return'apple'\n";
          }else if( Workspace::bmp->bXcode11 ||
                    Workspace::bmp->bXcode12 ||
                    Workspace::bmp->bXcode14 ){
            out << "  return'apple'\n";
          }else if( Workspace::bmp->bVS2019 ||
                    Workspace::bmp->bVS2022 ){
            out << "  return'microsoft'\n";
          }else{
            out << "  return'community'\n";
          }
          out << "end,\n";

        //}:                                      |
        //save:{                                  |

          out << "save = function(self)\n";
          out << "  out.save(out.generate(self),'tmp')\n";
          out << "end,\n";

        //}:                                      |
        //name:{                                  |

          out << "name = function()\n";
          out << "  " << getPlatformName() << "\n";
          out << "end,\n";

        //}:                                      |
        //is:{                                    |

          out << "is = function(name)\n";
          #if e_compiling( osx )
            out << "  return( name=='apple' )\n";
          #elif e_compiling( microsoft )
            out << "  return( name=='win64' )or( name=='microsoft' )\n";
          #elif e_compiling( linux )
            out << "  return( name=='linux' )\n";
          #else
            out << "  return nil\n";
          #endif
          out << "end,\n";

        //}:                                      |
        //----------------------------------------|-----------------------------

        out << "}\n";
        return out;
      }
    }

  //}:                                            |
  //[globals]:{                                   |

    string            Workspace::gen;
    string            Workspace::ext;
    Workspace::States Workspace::bmp;

  //}:                                            |
  //generate:{                                    |

    namespace{

      int generate( const string& cgf ){

        //----------------------------------------------------------------------
        // Must always create the tmp directory.
        //----------------------------------------------------------------------

        if( !IEngine::dexists( "tmp" )){
          IEngine::mkdir( "tmp" );
        }

        //----------------------------------------------------------------------
        // Generate template project and return.
        //----------------------------------------------------------------------

        if( Workspace::bmp->bGenerate ){

          //--------------------------------------|-----------------------------
          //MaxPlugin:{                           |

            #if e_compiling( microsoft )
              if( Workspace::bmp->bMaxPlugin ){

                //--------------------------------------------------------------
                // Write out the .DEF file.
                //--------------------------------------------------------------

                { Writer w( e_xfs( "tmp/%s.def", ccp( Workspace::gen )), kTEXT );
                  w.write( e_xfs(
                      "LIBRARY %s.dlu\n"
                    , ccp( Workspace::gen )));
                  w.write( "EXPORTS\n" );
                  w.write( "  LibDescription   @1\n" );
                  w.write( "  LibNumberClasses @2\n" );
                  w.write( "  LibClassDesc     @3\n" );
                  w.write( "  LibVersion       @4\n" );
                  w.save();
                }

                //--------------------------------------------------------------
                // Write out the cogfile.lua and platform lua files.
                //--------------------------------------------------------------

                { Writer w( "tmp/cogfile.lua", kTEXT );
                  w.write( "if platform.is'apple'then\n" );
                  w.write( "  require'cogfile.xcode.lua'\n" );
                  w.write( "elseif platform.is'microsoft'then\n" );
                  w.write( "  require'cogfile.vs2019.lua'\n" );
                  w.write( "elseif platform.is'linux'then\n" );
                  w.write( "  require'cogfile.linux.lua'\n" );
                  w.write( "end\n" );
                  w.save();
                }
                { Writer w( "tmp/cogfile.xcode.lua", kTEXT );
                  w.save();
                }
                { Writer w( "tmp/cogfile.linux.lua", kTEXT );
                  w.save();
                }
                { Writer w( "tmp/cogfile.vs2019.lua", kTEXT );
                  w.save();
                }
                return 0;
              }
            #endif

          //}:                                    |
          //--------------------------------------|-----------------------------

          return-1;
        }

        //----------------------------------------------------------------------
        // Create Lua context, setup options on it, and run sandboxed script.
        //----------------------------------------------------------------------

        const auto& createLua=[&]( const ccp pBuffer ){
          Lua::handle hLua = e_new<Lua>();
          auto& lua = hLua.cast();
          lua.sandbox( platformClass() );
          lua.sandbox( kWorkspace );
          string sBuffer( pBuffer );
          sBuffer.replace( "${RELEASE}"
            , "release" );
          sBuffer.replace( "${DEBUG}"
            , "debug" );
          if( Workspace::bmp->bXcode11 ||
              Workspace::bmp->bXcode12 ||
              Workspace::bmp->bXcode14 ){
            if( Workspace::bmp->osMac ){
              sBuffer.replace( "${PLATFORM}"
                , "macos"
              );
            }else{
              sBuffer.replace( "${SUBPLATFORM}"
                , "ios" );
              sBuffer.replace( "${PLATFORM}"
                , "macos"
              );
            }
          }else if( Workspace::bmp->bGradle ){
            if( Workspace::bmp->bNDK ){
              sBuffer.replace( "${PLATFORM}"
                , "android"
              );
            }
          }else if( Workspace::bmp->bNinja ){
            sBuffer.replace( "${PLATFORM}"
              , "linux"
            );
          }else if( Workspace::bmp->bVS2019 ||
                    Workspace::bmp->bVS2022 ){
            sBuffer.replace( "${PLATFORM}"
              , "windows"
            );
          }
          return hLua;
        };

        //----------------------------------------------------------------------
        // Load the script and run it in Lua VM.
        //----------------------------------------------------------------------

        const auto& st = e_fload( cgf );
        if( st.empty() )
          return-1;
        st.query(
          [&]( ccp pBuffer ){
            auto hLua = createLua( pBuffer );
            auto& lua = *hLua;

            //------------------------------------------------------------------
            // Make local options.
            //------------------------------------------------------------------

            string equ = "local options={";
            if( Workspace::bmp->bXcode14 ){
              equ << "\n  xcode14 = true,";
            }else{
              equ << "\n  xcode14 = false,";
            }
            if( Workspace::bmp->bXcode12 ){
              equ << "\n  xcode12 = true,";
            }else{
              equ << "\n  xcode12 = false,";
            }
            if( Workspace::bmp->bXcode11 ){
              equ << "\n  xcode11 = true,";
            }else{
              equ << "\n  xcode11 = false,";
            }
            if( Workspace::bmp->bVS2022 ){
              equ << "\n  vs2022 = true,";
            }else{
              equ << "\n  vs2022 = false,";
            }
            if( Workspace::bmp->bVS2019 ){
              equ << "\n  vs2019 = true,";
            }else{
              equ << "\n  vs2019 = false,";
            }
            if( Workspace::bmp->bEmscripten ){
              equ << "\n  emscripten = true,";
              equ << "\n  wasm = true,";
            }else{
              equ << "\n  emscripten = false,";
              equ << "\n  wasm = false,";
            }
            if( Workspace::bmp->bQmake ){
              equ << "\n  qmake = true,";
            }else{
              equ << "\n  qmake = false,";
            }
            if( Workspace::bmp->bNinja ){
              equ << "\n  ninja = true,";
            }else{
              equ << "\n  ninja = false,";
            }
            if( Workspace::bmp->bNDK ){
              equ << "\n  ndk = true,";
            }else{
              equ << "\n  ndk = false,";
            }
            equ << "\n}\n";

            //------------------------------------------------------------------
            // Create the targeted script and sandbox it. Gets called twice if
            // generating for ios and macos simultaneously.
            //------------------------------------------------------------------

            const auto& targets = Workspace::getTargets();
            auto targetedScript = ( equ + pBuffer );
            auto it = targets.getIterator();
            while( it ){
              lua.initialise();
              lua.sandbox(
                platformClass() );
              lua.sandbox(
                kWorkspace );
              const auto& l
                = "__target = \""
                + *it
                + "\"\n"
                + targetedScript;
              if( !lua.sandbox( l )){
            DEBUG_BREAK
              }
              ++it;
            }
            lua.save();
          }
        );
        e_msgf(
          "ok" );
        return 0;
      }
    }

  //}:                                            |
//}:                                              |
//Enginey:{                                       |
  //main:{                                        |

    int IEngine::main( const strings& args ){

      //------------------------------------------|-----------------------------
      //Versioning:{                              |

        //----------------------------------------------------------------------
        // 1.4.6.x  Introduction of template generation; added for my new book:
        // Metal, The Dark Arts.
        //----------------------------------------------------------------------
        // 1.4.7.x  Latest version with bug fixes.
        //----------------------------------------------------------------------
        // 1.4.8.x  Expanded command line arguments to support packaging multi-
        // directories and multiple files. This will be really critical for a
        // cross platform framework I'm planning with all platform shared lib
        // and header files. Binary and much simpler than macOS and iOS etc.
        //----------------------------------------------------------------------
        // 1.4.9.x  Addeds support for TBD libraries.
        //----------------------------------------------------------------------
        // 1.5.0.x  Upgraded Lua to 5.4.0.
        //----------------------------------------------------------------------
        // 1.5.1.x  Introducing load_all keyword for macOS. It enables all the
        // symbols of a static library to be exported from a framework. This'
        // needed by Swordlight so it only has to link against eon.framework.
        //----------------------------------------------------------------------
        // 1.5.2.x  Added --clean option instead of automatically deleting tmp.
        //----------------------------------------------------------------------
        // 1.5.3.x  Added Xcode project sorting and lots of other little tweaks
        // for compiling Swordlight and EON on Big Sur.  Added ability to turn
        // off universal builds.
        //----------------------------------------------------------------------
        // 1.5.4.x  Added more robust logic behind ignore().
        //----------------------------------------------------------------------
        // 1.5.5.x  Moved "--unity" switch out of the command line and into the
        // Lua scripts. It doesn't make sense to have unity builds for all
        // sub-projects, especially third party ones.
        //----------------------------------------------------------------------
        // 1.5.6.x  Added embedAndSign keyword to Xcode projects.
        //----------------------------------------------------------------------
        // 1.5.7.x  Added ability to use tables for all commands. Tables are a
        // excellent way to pass in a class instance to the generator instead
        // of a string.  Also added to this version is proper shared library
        // support.
        //----------------------------------------------------------------------
        // 1.5.8.x  Overhauled the plist handling in the Xcode backend and sign
        // setup. Lots of bug fixes and code refactoring.
        //----------------------------------------------------------------------
        // 1.6.0.x  Added support for macOS bundles. These are used as plugins
        // into the Player and Swordlight projects. Big version jump, because
        // bundles are a really major feature.
        //----------------------------------------------------------------------
        // 1.6.1.x  Added ability to set the library directory path from Lua.
        //----------------------------------------------------------------------
        // 1.6.2.x  Added toolchain keyword to Windows generator.
        //----------------------------------------------------------------------
        // 1.6.3.x  Added ignore filtering to Ninja serializer.
        //----------------------------------------------------------------------
        // 1.6.4.x  Added ability to disable embedding for Xcode bundles.
        //----------------------------------------------------------------------
        // 1.6.5.x  Added dependency syntax to Lua scripts.
        //----------------------------------------------------------------------
        // 1.6.6.x  Upgraded to latest Xcode.
        //----------------------------------------------------------------------
        // 1.6.7.x  Added proper PCH creation/using for MSVC.
        //----------------------------------------------------------------------
        // 1.6.8.x  Upgrading to 11.6 SDK and deployment target (Mac).
        //----------------------------------------------------------------------
        // 1.6.9.x  Added support for Visual Studio 2022.
        // 1.6.9.1  Added hooks for Windows into dependencies.
        // 1.6.9.2  Fixed problem with embedding dylibs.
        //----------------------------------------------------------------------
        // 1.7.0.x  Fixed a major bug finding macOS SDK root.
        //----------------------------------------------------------------------
        // 1.7.1.x  Large revamp for Windows: chiefly extended support for MSVC
        // 2022 and C++20. Also added LTSC whole program optimizations. Big
        // ver update because of all the changes for Windows that went in. The
        // macOS build will continue to be stable on 1.7.0.
        //----------------------------------------------------------------------
        // 1.7.2.x  Fixed a bug that causes cog to lockup with string equates.
        //----------------------------------------------------------------------
        // 1.7.3.x  Added support for Apple Silicon targets, not Universal
        // ones.
        //----------------------------------------------------------------------
        // 1.7.4.x  Added .eon files to list of possible resources.
        //----------------------------------------------------------------------
        // 1.7.5.x  Added first entitlements file.
        //----------------------------------------------------------------------
        // 1.7.6.x  Added "iOS iPadOS macOS" builds as command line option(s).
        // 1.7.6.1  Fixed a generation bug that chewed up the PBXNativeTarget.
        // 1.7.6.2  Fixed more bugs, this time testing in the debugger.
        // 1.7.6.6  Overhauled the generator for iOS (previous borked).
        // 1.7.6.7  Added overhaul of writePBXProjectSection (xcode.cpp).
        // 1.7.6.8  Forgot to increment an iterator.
        // 1.7.6.9  Approaching final code.
        //----------------------------------------------------------------------
        // 1.7.7.x  Intermediate build, working hard on ios path bug fixing.
        // 1.7.7.1  Nasty bug fixed in find_includes().
        // 1.7.7.2  Fixed some bugs in std generator.
        //----------------------------------------------------------------------
        // 1.7.8.x  Finally got iOS and macOS target working
        // This was a really big rewrite
        // Very happy with the outcome
        // 1.7.8.1  Fixed some generation bugs to do with bundles
        // 1.7.8.2  Hunted down and killed a lua_next() bug
        // 1.7.8.3  Fixed a nasty bug where `cog --clean` didn't work properly
        // 1.7.8.4  Fixed a nasty bug where `cog` resulted in empty targets
        // 1.7.8.5  Fixed a nasty bug where `cog` ignored `links_with`
        // 1.7.8.6  Fixed a nasty bug where `cog` resulted in red include group
        // 1.7.8.7  For some reason the frameworks didn't get included
        // 1.7.8.8  Big oops; fixed a bug where embedding was broken
        // 1.7.8.9  Fixed pulling in .xcassets packages.
        //----------------------------------------------------------------------
        // 1.7.9.x  Embedding entitlements into xcodeproj package, suppressing
        // "references" group if none exist.
        // 1.7.9.1  Building for universal.
        // 1.7.9.2  Removed find_includes; the functionality was duplicated by
        // find_sources. So, the .cpp files were duplicated because find_inc*
        // went through the exact same code path and blew everything all up.
        // This build also features new appending functionality for defines.
        // I also added the ability to pass a table into wsp:defines.
        // 1.7.9.3  Fixed a bunch of bugs in the embedded Lua code (above).
        // 1.7.9.4  More bug fixing in workspace:defines(); should be good.
        // 1.7.9.5  You can now dump anything passed to Lua::sandbox().
        // 1.7.9.6  To catch a bug; added DUMP_SCRIPT cvar.
        // 1.7.9.7  The Lua 'workspace' variable is global.
        // 1.7.9.8  Another debugging build.
        // 1.7.9.9  Fixed the bloody thing!
        // 1.7.9.10 Fixed a crash after generation.
        // 1.7.9.11 Fixed another crash.
        // 1.7.9.12 Fixed a bug in Xcode generator where nothing is written to
        // the .xcworkspace folders. We should see a ton of libraries, and the
        // the .xcodeproj's generated too. The problem was we were using src**
        // not the m_libraryPaths!
        // 1.7.9.13 Fixed another problem with the Xcode backendf generator. It
        // was stopping any .xcodeproj's from being generated again.
        // 1.7.9.14 Fixed a bad compilation with clang.
        // srcInc was missing.
        // 1.7.9.15 This is an attempt to get the defines working properly. At
        // the moment there's a lot of problems with it it isn't recognized by
        // the backend when I pass in a table. Bug juice!
        //----------------------------------------------------------------------
        // 1.8.0.x  A _huge_ milestone: lots of features!
        // 1.8.0.1  Added some more error messahes for #include<>; #include""
        // is completely illegal at the moment.
        // 1.8.0.2  Making it so I can generate for Ninja everywhere.
        // 1.8.0.3  Debugging the Ninja process.
        // 1.8.0.4  No more platform specifics.
        // 1.8.0.5  Added /utf-8 option.
        // 1.8.0.6  Squashed a crash.
        // 1.8.0.7  Addd Android support via NDK; applications and libraries.
        //----------------------------------------------------------------------
        // 1.8.1.x  Finished (mostly) Gradle/NDK generator.
        // 1.8.1.1  Added repositories to Gradle generator.
        // 1.8.1.2  Took out annoying C++ language logging.
        // 1.8.1.3  Adding framework path: /Library/Frameworks when looking for
        // frameworks to link with; this is cheifly for linking third party API
        // like Mono into the project.
        //----------------------------------------------------------------------

        static constexpr u8 major = 0x01; // Each has 16 steps: 0x0 thru 0xF.
        static constexpr u8 minor = 0x08;
        static constexpr u8 rev   = 0x01;
        static constexpr u8 build = 0x03;

        //----------------------------------------------------------------------
        // Message out the version.
        //----------------------------------------------------------------------

        if( build ){
          e_msgf( "Cog pre-build system v%u.%u.%u (build %u)"
            , u32( major )
            , u32( minor )
            , u32( rev   )
            , u32( build )
          );
        }else{
          e_msgf( "Cog pre-build system v%u.%u.%u"
            , u32( major )
            , u32( minor )
            , u32( rev   )
          );
        }

      //}:                                        |
      //------------------------------------------|-----------------------------
      //                                          :
      //                                          :
      //                                          :
      //------------------------------------------|-----------------------------
      //Options:{                                 |
        //Projects options:{                      |

          //--------------------------------------------------------------------
          // Run through all the arguments seting options as we go. Final non
          // long or short option will generate from arg as filename.
          //--------------------------------------------------------------------

          auto it = args.getIterator();
          while( ++it ){
            switch( **it ){

              //----------------------------------------------------------------
              // Long options.
              //----------------------------------------------------------------

              case'-':

                //--------------------------------------------------------------
                // Enable iOS builds with or without macOS support too. Note to
                // self: cog does not support AppleTV (tvOS) in any form.
                //--------------------------------------------------------------

                if( it->tolower() == "--xcode"_64 ){
                  Workspace::bmp->bXcode12 = 1;
                  Workspace::bmp->osMac = 1;
                }else if( it->tolower().left( 8 )=="--xcode="_64 ){
                  auto targets = it->tolower().ltrimmed( 8 );
                  if( targets.replace( "macos", "" )){
                    Workspace::bmp->bXcode12 = 1;
                    Workspace::bmp->osMac = 1;
                  }
                  if( targets.replace( "ios", "" )){
                    Workspace::bmp->bXcode12 = 1;
                    Workspace::bmp->osIphone = 1;
                  }
                  if( Workspace::bmp->osIphone &&
                      Workspace::bmp->osMac ){
                    Workspace::bmp->bXcode12 = 1;
                    Workspace::bmp->allApple = 1;
                  }
                  continue;
                }

                //--------------------------------------------------------------
                // Enable unity builds.
                //--------------------------------------------------------------

                if( it->tolower().hash() == "--unity"_64 ){
                  Workspace::bmp->bUnity = 1;
                  continue;
                }

                //--------------------------------------------------------------
                // Delete tmp directory.
                //--------------------------------------------------------------

                if( it->tolower().hash() == "--clean"_64 ){
                  IEngine::rm( "tmp" );
                  continue;
                }

                //--------------------------------------------------------------
                // Package up a directory.
                //--------------------------------------------------------------

                #if 0
                  if( it->left( 10 ).tolower().hash() == "--package="_64 ){
                    const auto& pkgName = it->ltrimmed( 10 );
                    if( !++it ){
                      e_errorf( 81723, "missing directory name!" );
                      return-1;
                    }
                    onPackage( it, pkgName );
                    return 0;
                  }
                #endif

                //--------------------------------------------------------------
                // Generating from templates.
                //--------------------------------------------------------------

                #if 0
                  if( it->left( 11 ).tolower().hash() == "--unpackage"_64 ){
                    if( !++it ){
                      e_errorf( 19283, "missing directory name!" );
                      return-1;
                    }
                    onUnpackage( *it );
                    return 0;
                  }
                #endif

                //--------------------------------------------------------------
                // Tweak output DLL (if there is one)  to be a 3D Studio Max
                // plugin.  This functionality is only available on Windows
                // because macOS has no support for 3D Studio Max. If it was
                // Maya this would be a very different proposition.
                //--------------------------------------------------------------

                #if e_compiling( microsoft )
                  if( it->trimmed( 4 ).tolower().hash() == "--maxplugin="_64 ){
                    Workspace::ext = it->ltrimmed( it->len() - 4 );
                    Workspace::bmp->bMaxPlugin = 1;
                    break;
                  }
                #endif

                //--------------------------------------------------------------
                // Export to Ninja using emscripten and web assembly not C++.
                //--------------------------------------------------------------

                // Handle emscripten and wasm options.
                if(( it->hash() == "--emscripten"_64 )||(
                     it->hash() == "--wasm"_64 )){
                  Workspace::bmp->bEmscripten = 1;
                  Workspace::bmp->bNinja      = 1;
                  continue;
                }

                // Handle ninja option except on linux where it is the default.
                if( it->hash() == "--ninja"_64 ){
                  Workspace::bmp->bNinja = 1;
                  continue;
                }

                //--------------------------------------------------------------
                // Versioning saved back out on --version.
                //--------------------------------------------------------------

                //TODO: Rewrite this so it works better or rip it out.
                #if 0
                  if( it->left( 6 ).hash() == "--ver="_64 ){
                    cp  p = cp( it->c_str() + 6 );
                    cp  e = strchr( p, '.' );
                    u32 x = major;
                    u32 y = minor;
                    u32 z = rev;
                    u32 w = build;
                    if( e ){
                      *e = 0;
                      x = u32( atoi( p ));
                      p = e + 1;
                    }
                    e = strchr( p, '.' );
                    if( e ){
                      *e = 0;
                      y = u32( atoi( p ));
                      p = e + 1;
                    }
                    e = strchr( p, '.' );
                    if( e ){
                      z = u32( atoi( p ));
                      p = e + 1;
                    }
                    e = strchr( p, 0 );
                    if( e ){
                      w = u32( atoi( p ));
                    }
                    major = u8( x & 0xFF );
                    minor = u8( y & 0xFF );
                    rev   = u8( z & 0xFF );
                    build = u8( w & 0xFF );
                    { Writer fs( ".cog", kCOMPRESS|kNOEXT );
                      fs << major; // Major version
                      fs << minor; // Minor version
                      fs << rev;   // Revision version
                      fs << build; // Build version
                      fs.save( "Cog" ); // Makes an EON asset.
                    }
                    { Writer fs( "version.h", kTEXT );
                      fs << e_xfs(
                        "#define COG_BUILD_VERSION 0x%08x\n"
                        , u32( major << 24 )
                        | u32( minor << 16 )
                        | u32( rev   <<  8 )
                        | u32( build ));
                      fs << e_xfs(
                        "#define COG_BUILD_MAJOR    %u\n"
                        , u32( major ));
                      fs << e_xfs(
                        "#define COG_BUILD_MINOR    %u\n"
                        , u32( minor ));
                      fs << e_xfs(
                        "#define COG_BUILD_REVISION %u\n"
                        , u32( rev ));
                      fs << e_xfs(
                        "#define COG_BUILD_BUILD    %u\n"
                        , u32( build ));
                      fs.save();
                    }
                    break;
                  }
                #endif

                //--------------------------------------------------------------
                // Export a Qmake project.
                //--------------------------------------------------------------

                if( it->hash() == "--qmake"_64 ){
                  Workspace::bmp->bQmake = 1;
                  continue;
                }

                //--------------------------------------------------------------
                // Export an Android gradle project.
                //
                // TODO: --ndk=gradle,cmake might be awesome too, just an idea.
                //--------------------------------------------------------------

                if( it->hash() == "--ndk"_64 ){
                  Workspace::bmp->bGradle = 1;
                  Workspace::bmp->bNDK    = 1;
                  continue;
                }

                //--------------------------------------------------------------
                // Export a Visual Studio 2022 project instead of default 2019.
                //--------------------------------------------------------------

                if( it->hash() == "--vs2022=v143"_64 ){
                  Workspace::bmp->bVSTools143 = 1;
                  Workspace::bmp->bVS2022     = 1;
                  continue;
                }
                if( it->hash() == "--vs2022"_64 ){
                  Workspace::bmp->bVS2022 = 1;
                  continue;
                }
                switch( it->hash() ){
                  case"--c++20"_64:
                  case"--cxx20"_64:
                  case"--cpp20"_64:
                    Workspace::bmp->uLanguage = 20;
                    break;
                  case"--c++17"_64:
                  case"--cxx17"_64:
                  case"--cpp17"_64:
                    Workspace::bmp->uLanguage = 17;
                    break;
                  case"--c++14"_64:
                  case"--cxx14"_64:
                  case"--cpp14"_64:
                    Workspace::bmp->uLanguage = 14;
                    break;
                  case"--c++11"_64:
                  case"--cxx11"_64:
                  case"--cpp11"_64:
                    Workspace::bmp->uLanguage = 11;
                    break;
                }

                //--------------------------------------------------------------
                // Handle the MT NO DLL case for compiling.
                //--------------------------------------------------------------

                #if e_compiling( microsoft )
                  switch( it->hash() ){
                    case"--mtdll=false"_64:
                      [[fallthrough]];
                    case"--mtdll=no"_64:
                      Workspace::bmp->bVSMTNoDLL = 1;
                      break;
                  }
                #endif


                //--------------------------------------------------------------
                // Export an Xcode 1x project instead of the default 12.
                //--------------------------------------------------------------

                if( it->hash() == "--xcode14"_64 ){
                  Workspace::bmp.all       = 0;
                  Workspace::bmp->bXcode14 = 1;
                  break;
                }
                if( it->hash() == "--xcode12"_64 ){
                  Workspace::bmp.all       = 0;
                  Workspace::bmp->bXcode12 = 1;
                  break;
                }
                if( it->hash() == "--xcode11"_64 ){
                  Workspace::bmp.all       = 0;
                  Workspace::bmp->bXcode11 = 1;
                  break;
                }

                //--------------------------------------------------------------
                // Help option.
                //--------------------------------------------------------------

                if( it->hash() == "--help"_64 ){
                  e_msgf( "  Usage cog [options] [cogfile.lua]" );
                  e_msgf( "    options:" );
                  e_msgf( "      --unity" );
                  e_msgf( "      --clean" );
                  e_msgf( "      --qmake" );//TODO: Rip out all of cog's Qmake code.
                  e_msgf( "      --xcode or --xcode=[macos|ios]" );
                  e_msgf( "      --c++{20|17|14|11} (default is 17)" );
                  e_msgf( "      --vs2022[=v143]" );
                  e_msgf( "      --emscripten \\__ Web Assembly" );
                  e_msgf( "      --wasm       /" );
                  e_msgf( "      --ndk" );
                  return 0;
                }
                break;

              //----------------------------------------------------------------
              // Everything else runs generator.
              //----------------------------------------------------------------

              default:
                if( !fexists( *it )){
                  e_warnsf( "  * %s not found; ignored!", ccp( *it ));
                }else{
                  return generate( *it );
                }
                break;
            }
          }

        //}:                                      |
      //}:                                        |
      //------------------------------------------|-----------------------------

      if( !fexists( "cogfile.lua" )){
        e_errorf( 98234, "cogfile.lua not found!" );
        return -1;
      }
      if( !Workspace::bmp.all )
        return-1;
      generate( "cogfile.lua" );
      return 0;
    }

  //}:                                            |
//}:                                              |
//------------------------------------------------|-----------------------------
