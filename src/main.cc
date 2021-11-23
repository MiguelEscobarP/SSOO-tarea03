#include <iostream>    
#include <fstream>
#include <queue>       
#include <future>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <csignal>
#include <unistd.h>

void signal_handler(int signal_num)
{
	std::cout<<"Detención no permitida"<<std::endl;     //atrapa las señales
}

int main(int argc, char *argv[])
{
  int h=-1;
	pid_t pid = fork(); //se crea un proceso hijo 

	std::signal(SIGINT, signal_handler);/*ctrl+c*/    //register the signals and the signal handler
	std::signal(SIGTSTP, signal_handler);/*ctrl+z*/
	std::signal(SIGQUIT, signal_handler);/*ctrl+\*/

	for (int i=0;i<50;i+=1)
	{
		if (pid == 0){ 
      //impar
			//std::cout << "soy el proce hijo :" << getpid() << std::endl;
			h=h+2;
			
				std::this_thread::sleep_for(std::chrono::seconds(1));
				std::cout << "Valor Impar: " << h <<" - PID = "<<getpid()<< std::endl;

		}
		else{
      //fibonacci
			long int a = 0, b = 1, c = 1;
			if (i == 0)//si es el primer numero de la sucecion es 1 
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				std::cout << " Valor Fibonacci: 1 - PPIDE = "<<getpid()<<std::endl;
			}
			else // si no es el primer numero se calcula el numero
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				for (int j = 0; j < i; j++)
				{
					c=a+b;
					a=b;
					b=c;
				}
				std::cout << "Valor Fibonacci: "<<c<<" - PPIDE = "<<getpid()<<std::endl;
			}
		}
	}
	std::raise(SIGTERM);  //señal de termino 

	return EXIT_SUCCESS;
}
