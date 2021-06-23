// Versão para Windows

#include <iostream>
#include <string>
#include <cstdlib>
#include <Windows.h>

void cor(int valor);

std::string retorno(std::string comando);

int main(int argv, char* argc[]){

  cor(7);

  std::string caminho = "";

  int min = 0, max = 0, acertos = 0;

  for(int c=1;c<argv;c++){

    if((std::string) argc[c] == "-h"){

      std::cout << std::endl << "-h : ajuda" << std::endl <<
      "-n : numero de casos, a partir do 0 [-n max]" << std::endl <<
      "-i : intervalo de casos [-i min max]" << std::endl <<
      "-c : caminho do programa [-c C:...\\main.exe]" << std::endl;
      return 0;
    }

    if((std::string) argc[c] == "-c"){

      caminho = argc[c+1];
      continue;

    }

    if((std::string) argc[c] == "-n"){

      max = atoi(argc[c+1]);
      continue;

    }

    if((std::string) argc[c] == "-i"){

      if(argv < c+2){

        std::cout << "Comando invalido" << std::endl;
        return 1;

      }

      min = atoi(argc[c+1])-1;
      max = atoi(argc[c+2]);

      if(min > max){

          int inter = max;
          max = min;
          min = inter;

      }

      continue;

    }

  }

  if(caminho == ""){

    std::cout << "Digite o caminho do programa:";

    std::cin >> caminho;

  }

  if(max == 0){

    std::cout << "Digite o numero de casos:";

    std::cin >> max;

  }

  for(int c=min+1;c<max+1;c++){

      std::cout <<std::endl << "Caso [" << c << "]: ";

      std::string r_1 = retorno((std::string("type ") + std::to_string(c) + std::string(".in" " | ") + caminho));

      std::string r_2 = retorno(std::string("type ") + std::to_string(c) + std::string(".out"));

      if(r_1 == "ERRO" || r_2 == "ERRO") {

        std::cout << "Erro" << std::endl;
        continue;

      }

      if(r_1 == r_2){

        cor(2);

        std::cout << "Correto" << std::endl;
        acertos++;

        cor(7);

      }
      else{

        cor(4);

        std::cout << "Errado" << std::endl;

        cor(7);

        std::cout << std::endl << "Resultado: " << std::endl << r_1 << std::endl << "Esperado: " << std::endl << r_2 << std::endl;

      }

  }

  std::cout << std::endl << "Nota: " << acertos << "\\" << max-min << std::endl;

  return 0;
}


void cor(int valor){

  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),valor);

}

std::string retorno(std::string comando){

  char buffer[128];

  std::string r = "";

  FILE *f = popen(comando.c_str(),"r");

  if(!f) return "ERRO";

  else while(!feof(f)) if(fgets(buffer,128,f) != NULL) r += buffer;

  return r;

}
