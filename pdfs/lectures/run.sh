input="files"
while IFS= read -r line
do
  wget "$line"
done < "$input"