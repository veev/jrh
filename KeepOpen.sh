#!/bin/sh
if [ $(ps ax | grep -v grep | grep "JRHMemorialWall.app" | wc -l) -eq 0 ]
then
echo "JRHMemorialWall not running. opening…"
open /OpenFrameworks/of_v0.8.3_osx_release/apps/jrh/JRHMemorialWall/bin/JRHMemorialWall.app
else
echo "JRHMemorialWall running"
fi