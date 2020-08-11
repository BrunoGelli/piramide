#!/bin/bash


start=$SECONDS

echo "Running for several XARAPUCAS with different numbers of SiPMs."

rm FiltroOutPut.txt


    # start_i=$SECONDS

    # echo "Running for 1 SiPMs"
    # ./filtro filtro.in 1 >/dev/null

    # duration=$(( SECONDS - start_i ))
    # echo "Completed in $(printf '%d' $duration) seconds."


for ((i=20;i<=50;i=i+1)); do
    start_i=$SECONDS

    echo "Running for $(printf '%d' $i) SiPMs"
    ./filtro filtro.in $(printf '0.%d' $i) >/dev/null

    duration=$(( SECONDS - start_i ))
    echo "Completed in $(printf '%d' $duration) seconds."
done

duration=$(( SECONDS - start ))

if (( $duration >= 3600 )) ; then
    let "hours=SECONDS/3600"
    let "minutes=(SECONDS%3600)/60"
    let "seconds=(SECONDS%3600)%60"
    echo "Completed in $hours hour(s), $minutes minute(s) and $seconds second(s)" 
elif (( $duration >= 60 )) ; then
    let "minutes=(SECONDS%3600)/60"
    let "seconds=(SECONDS%3600)%60"
    echo "Completed in $minutes minute(s) and $seconds second(s)"
else
    echo "Completed in $SECONDS seconds"
fi

root -l ana.C