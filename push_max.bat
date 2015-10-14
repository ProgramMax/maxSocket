@echo off

IF %1.==. GOTO NoBranchName

git subtree push --prefix=Libraries/max max %1
GOTO End

:NoBranchName
	# if we don't have a parameter for the branch name
	ECHO Usage: ./push_max.bat <branch_name>
	GOTO End

:End