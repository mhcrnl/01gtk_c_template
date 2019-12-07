#!/bin/bash

DATE=`date`

bzr add .
bzr commit -m "$DATE"
bzr push lp:01c
