gcc -o compilado *.c
if [ $? -eq 0 ];then 
   echo "compilado com sucesso!"
   ./compilado < in.txt > result.txt
else
   echo "nao compilado"
fi