
 
  solution "0MySolution"

	-- Multithreaded compiling
	if _ACTION == "vs2010" or _ACTION=="vs2008" then
		buildoptions { "/MP"  }
	end 
	
    
	configurations {"Release", "Debug"}
	configuration "Release"
		flags { "Optimize", "StaticRuntime", "NoMinimalRebuild", "FloatFast"}
	configuration "Debug"
		defines {"_DEBUG=1"}
		flags { "Symbols", "StaticRuntime" , "NoMinimalRebuild", "NoEditAndContinue" ,"FloatFast"}
		
	platforms {"x32", "x64"}

	configuration {"x32"}
		targetsuffix ("_" .. _ACTION)
	configuration "x64"		
		targetsuffix ("_" .. _ACTION .. "_64" )
	configuration {"x64", "debug"}
		targetsuffix ("_" .. _ACTION .. "_x64_debug")
	configuration {"x64", "release"}
		targetsuffix ("_" .. _ACTION .. "_x64_release" )
	configuration {"x32", "debug"}
		targetsuffix ("_" .. _ACTION .. "_debug" )
	
	configuration{}

	flags { "NoRTTI", "NoExceptions"}
	defines { "_HAS_EXCEPTIONS=0" }
	targetdir "../bin"
  location("./" .. _ACTION)
	

	projectRootDir = os.getcwd() .. "/../"
	print("Project root directroy: " .. projectRootDir);

	dofile ("findOpenCL.lua")
	dofile ("findDirectX11.lua")
	dofile ("findOpenGLGlewGlut.lua")
	
	language "C++"
	

--	include "../bullet2"	
--	include "../jpeglib"

	include "../src"	
	include "../examples/rendertest"
	include "../bullet2"
	
--	include "../examples/OpenGLTrueTypeFont"
