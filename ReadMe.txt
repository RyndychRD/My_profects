указатель на функцию
int f(int a,float b )
return (int(b))+a
}
int (*f)(int,float)=&f;
cout<<f(5,7.2)

