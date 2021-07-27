BEGIN{
c=0;
}
{
if($1=="d"){
c++;
}
}
END{
printf("The packet drop=%d\n",c);
}
