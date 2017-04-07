#!/bin/sh
# $0 is the script name, $1 id the first ARG, $2 is second...
addr="$1"
comm="chmod 777 /dev/bus/usb/"
eval $comm$addr


