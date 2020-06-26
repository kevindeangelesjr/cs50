#!/bin/bash

DEPLOY_PATH=/var/www/html # Deploy down webserver path
FILE=$1 # First argument

if [ $# -eq 0 ]; then
    echo "No argument provided"
    exit 1

### if only 1 argument, deploy that file with its current name
elif [ $# -eq 1 ]; then
    DEPLOY_FILE=$1

### If 2 arguments, deploy file with name supplied as second argument
elif [ $# -eq 2 ]; then
    DEPLOY_FILE=$2

elif [ $# -gt 2 ]; then
    echo "Please only provide one argument"
    exit 1
fi

if [ ! -f "$FILE" ]; then
    echo "Provided argument $FILE not a file"
    exit 1
fi

### Deploy file to webserver path
echo "Copying $FILE to $DEPLOY_PATH/$DEPLOY_FILE ... "
cp $FILE $DEPLOY_PATH/$DEPLOY_FILE

### Restart httpd service
echo "Reloading httpd ... "
systemctl reload httpd

### Ensure httpd was successfully reloaded
if [ $? -eq 0 ]; then
    echo "httpd successfully reloaded!"
    exit 0
else
    echo "httpd reload failed!"
    exit 1
fi