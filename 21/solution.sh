find "$1" -type f -name "Makefile*" | while read file
do
    sed -i 's#\\#/#g' "$file"
done
