input="files"
while IFS= read -r line
do
  wget "$line"
done < "$input"

perl-rename -i "s/(.*)(\.pdf)(\.[0-9]+)$/\1\3\2/" *