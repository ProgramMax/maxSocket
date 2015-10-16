if [ $# -lt 1 ]; then
	# if we don't have a parameter for the branch name
	echo 'Usage: ./push_max.sh <branch_name>'
else
	git subtree push --prefix=Libraries/max/ max $1
fi
