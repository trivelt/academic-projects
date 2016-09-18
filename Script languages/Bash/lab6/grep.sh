#!/bin/bash
# Maciej Michalec, grupa 2

DIR_LIST=()
PATTERN_LIST=()

CURRENT_DIR_LIST="" #() # lista katalogow dla aktualnie definiowanego wzorca
CURRENT_PATTERN_LIST="" #() # lista aktualnie definiowanych wzorcow

EXPECTED_DIRNAME=0
EXPECTED_PATTERN=0
EXPECTED_D_FLAG=1
CURRENT_PATTERN_SET=0
PATTERNS_COUNTER=0

for arg in "$@"; do
    if [ $arg = "-d" ]; then
        if [ $CURRENT_PATTERN_SET -eq 1 ]; then
            DIR_LIST[$PATTERNS_COUNTER]=$CURRENT_DIR_LIST 
            PATTERN_LIST[$PATTERNS_COUNTER]=$CURRENT_PATTERN_LIST

            PATTERNS_COUNTER=$((PATTERNS_COUNTER+1))

            CURRENT_DIR_LIST="" #()
            CURRENT_PATTERN_LIST="" #()
        fi
        EXPECTED_DIRNAME=1
        EXPECTED_PATTERN=0
        EXPECTED_D_FLAG=0
        CURRENT_PATTERN_SET=0        
    else
        if [ $EXPECTED_DIRNAME -eq 1 ]; then
            #CURRENT_DIR_LIST+=($arg)
            CURRENT_DIR_LIST=${CURRENT_DIR_LIST}";$arg"
            EXPECTED_DIRNAME=0
            EXPECTED_PATTERN=1
            EXPECTED_D_FLAG=1
        elif [ $EXPECTED_PATTERN -eq 1 ]; then
            #CURRENT_PATTERN_LIST+=($arg)
            CURRENT_PATTERN_LIST=${CURRENT_PATTERN_LIST}";$arg"
            EXPECTED_PATTERN=1
            EXPECTED_D_FLAG=1
            CURRENT_PATTERN_SET=1
        fi
    fi
done

if [ $CURRENT_PATTERN_SET -eq 1 ]; then
    DIR_LIST[$PATTERNS_COUNTER]=$CURRENT_DIR_LIST
    PATTERN_LIST[$PATTERNS_COUNTER]=$CURRENT_PATTERN_LIST
fi

i=0
while [ $i -le $PATTERNS_COUNTER ]; do
    TOTAL_COUNTER=0
    echo -n "== Wzorce:"
    IFS=';' read -r -a patterns <<< "${PATTERN_LIST[$i]}"
    for element in "${patterns[@]}"; do
        echo -n " $element"
    done
    echo " =="

    IFS=';' read -r -a directories <<< "${DIR_LIST[$i]}"
    for directory in "${directories[@]}"; do
        if [[ $directory = "" ]]; then
            continue
        fi
        LOCAL_COUNTER=0
        for filename in $(find $directory -name "*"); do    
            if [ -f $filename ]; then
                isFile=$(file -0 "$filename" | cut -d $'\0' -f2)
                case "$isFile" in
                (*text*)
                    ;;
                (*)
                    #echo "Binary file $filename"
                    continue
                    ;;
                esac
                while read line; do    
                    for pattern in "${patterns[@]}"; do
                        if [[ $pattern = "" ]]; then
                            continue
                        fi

                        if [[ "$line" =~ "$pattern" ]]; then
                            LOCAL_COUNTER=$((LOCAL_COUNTER+1))
                            TOTAL_COUNTER=$((TOTAL_COUNTER+1))
                        fi
                    done
                done < $filename
            fi
        done  
        echo "* $directory: $LOCAL_COUNTER" 
    done
    echo "* TOTAL: $TOTAL_COUNTER"
    i=$((i+1))
done
