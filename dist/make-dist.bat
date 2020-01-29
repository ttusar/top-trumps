cd ../src
git ls-files > files.txt
tar -cvzf ../dist/top-trumps.tar.gz --files-from=files.txt
