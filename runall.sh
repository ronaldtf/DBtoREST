#!/bin/bash

# This script starts the applications needed to run the project

ERROR=0

if test `ps -ef | grep -v grep | grep mysqld | wc -l` -ne 0; then
	echo "MySQL is already running"
else
	echo "Starting MySQL..."
	mysqld &
	if [ $? -ne 0 ]; then
		echo "ERROR: A problem occurred when trying to start MySQL server"
		echo "       Please verify mysql settings and retry again"
		ERROR=1
	fi
fi

if [ $ERROR -eq 0 ]; then
	if test `ps -ef | grep -v grep | grep http-server | wc -l` -ne 0; then
		echo "http-server is already running"
	else
		echo "Starting http-server..."
		cd swagger && http-server &
		if [ $? -ne 0 ]; then
			echo "WARN: A problem occurred when trying to start http-server"
			echo "      (this component is optional)"
			ERROR=0
		fi		
	fi
fi

if [ $ERROR -eq 0 ]; then
	if [[ $# -gt 0 ]] && [[ $1 == "cxx" ]]; then
		make runcxx
	elif [[ $# -gt 0 ]] && [[ $1 == "java" ]]; then
		make runjava
	else
		echo -e "\nERROR: Cannot determine language (options: java/cxx)\n"
	fi
fi
