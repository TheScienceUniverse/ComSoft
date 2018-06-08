#!/bin/bash

read -p "Enter file_name: " file

echo Creating Converter Program...
gcc -o H c2h.c

echo Making O/P file...
./H $file

echo Deleting created Program...
rm H

echo Your file is live at code.html
echo To view demo, open index.html
echo Thank You...!

#etc.
