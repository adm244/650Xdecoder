@ECHO OFF
REM This file is a part of cdev project
REM https://github.com/adm244/cdev

SETLOCAL
REM [customize those variables]
SET libs=kernel32.lib
SET common=%source%\common
SET tools_src=%source%\tools
SET files=%source%\main.c

REM SET opgen_libs=kernel32.lib
REM SET opgen_name=opgen
REM SET opgen_src=%tools_src%\%opgen_name%.c

SET debug=/Od /Zi /DDebug /nologo
SET release=/O2 /WX /nologo

REM SET opgen_args=%debug% /I%common% /Fe%opgen_name% %opgen_src% /link %opgen_libs%
SET args=%debug% /I%common% /Fe%project% %files% /link %libs%

SET compiler=CL
REM ###########################

SET edit=edit
SET setprjname=setname

IF [%1]==[%setprjname%] GOTO SetProjectName
IF [%1]==[%edit%] GOTO EditBuildFile
IF [%1]==[] GOTO Build
GOTO Error

:Build
ECHO:Build started...

IF NOT EXIST "%bin%" MKDIR "%bin%"
PUSHD "%bin%"

REM ECHO: Compiling %opgen_name%...
REM "%compiler%" %opgen_args%
REM IF NOT [%ERRORLEVEL%]==[0] GOTO CompileFailed
REM 
REM ECHO: Generating operations file...
REM CALL "%opgen_name%.exe"
REM IF NOT [%ERRORLEVEL%]==[0] GOTO GenFailed

ECHO: Compiling %project%...
"%compiler%" %args%
IF NOT [%ERRORLEVEL%]==[0] GOTO CompileFailed

POPD

ECHO:Build finished.
GOTO:EOF

:CompileFailed
ECHO:Compilation failed (%ERRORLEVEL% returned).
GOTO:EOF

:GenFailed
ECHO:Generation failed (%ERRORLEVEL% returned).
GOTO:EOF

:SetProjectName
IF [%2]==[] ECHO: ERROR: Name for a project was NOT specified! && GOTO:EOF

ECHO: Changing project name to %2...
ENDLOCAL
SET project=%2
ECHO: Done!
GOTO:EOF

:EditBuildFile
"%editor%" "%tools%\%~n0.bat"
GOTO:EOF

:Error
ECHO: ERROR: wrong arguments passed!
GOTO:EOF
