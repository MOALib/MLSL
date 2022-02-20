#!/bin/sh

F="d.mls";


echo "logmlsl.exe test";

if test -f "$F"; then
    echo "File $F exists."
else
    echo "File $F does not exist."
    exit 1;
fi


echo "logging";

./logmlsl.exe "$F" MLSL_NOTICE "User Kate Middleton Logged out";
./logmlsl.exe "$F" MLSL_HIGH_HEEL "High heel bought";
# ./logmlsl.exe "$F" MLSL_COMMENT "what is dis";

echo "done";