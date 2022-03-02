// Jaqueline de Lima Pereira
// Ricardo Henrique Bachião de Lima

#include <iostream>
#include <fstream>
using namespace std;

struct livro {
  string nome, emprestimo;
};

struct usuario {
  string nome, senha;
  int permissao;
};

int login() {
  string login, senha;
  cout << "Informe o nome de usuário: ";
  cin >> login;
  cout << "Informe a senha: ";
  cin >> senha;

  string u, s;
  int permissao;
  ifstream arquivo("usuarios.txt");
  while (arquivo >> u >> s >> permissao) {
    if (login == u && senha == s) {
      return permissao;
    }
  }
  arquivo.close();
  cout << endl;
  cout << "Usuário ou senha inválidos.\n";
  return -1;
}

void ver_livros() {
  cout << endl;
  ifstream livros("livros.txt");

  string nome_livro, emprestimo;
  while (livros >> nome_livro >> emprestimo) {
    cout << nome_livro << endl;
  }
  livros.close();
  cout << endl;
}

void buscar_livro() {
  string nome_busca;
  livro b;
  bool encontrou = false;
  cout << "Digite o nome do livro que deseja buscar: ";
  cin >> nome_busca;
  ifstream livros("livros.txt");
  while (livros >> b.nome >> b.emprestimo) {
    if (b.nome == nome_busca) {
      encontrou = true;
      cout << "Encontrado!\n";
      if (b.emprestimo == "0") {
        cout << "Este livro não está emprestado no momento.\n";
      }
      else {
        cout << "Este livro está emprestado para " << b.emprestimo << ".\n";
      }
    }
  }
  livros.close();
  if (encontrou == false) {
    cout << "Não encontrado.\n";
  }
}

void ver_emprestimos(livro e) {
  string usuario;
  cout << "Digite seu nome de usuario: ";
  cin >> usuario;
  cout << "\n";
  ifstream arquivo("livros.txt");
  while (arquivo >> e.nome >> e.emprestimo) {
    if (e.emprestimo == usuario) {
      cout << e.nome << endl;
    }
  }
  arquivo.close();
}

void inserir_livro(livro novo_livro){
  cout << "Digite o nome do livro: ";
  cin >> novo_livro.nome;
  cout << "\n";
  novo_livro.emprestimo = "0";
  ofstream books("livros.txt", ios::app);
  books << novo_livro.nome << " " << novo_livro.emprestimo << "\n";
  books.close();
}

void alterar_livro() {
  ifstream arquivo("livros.txt");
	if(!arquivo.is_open()){
		cout << "Falha ao abrir ao abrir o arquivo" << endl;
		return;
	}

  string nome;
  cout << "Digite o nome do livro que deseja alterar: ";
  cin >> nome;
	ofstream temp("temp.txt");
  string novo_nome;
	livro a;
	while(arquivo >> a.nome >> a.emprestimo){
		if(a.nome == nome){
      cout << "Digite o novo nome do livro: ";
      cin >> novo_nome;
      cout << endl;
			temp << novo_nome << " " << a.emprestimo << endl;
		}
		else{
			temp << a.nome << " " << a.emprestimo << endl;
		}
	}
	arquivo.close();
	temp.close();
	remove("livros.txt");
	rename("temp.txt", "livros.txt");
}

void excluir_livro() {
  ifstream arquivo("livros.txt");
	if(!arquivo.is_open()){
		cout << "Falha ao abrir ao abrir o arquivo" << endl;
		return;
	}

  string nome;
  cout << "Digite o nome do livro que deseja excluir: ";
  cin >> nome;
  cout << endl;
	ofstream temp("temp.txt");
	livro e;
	while(arquivo >> e.nome >> e.emprestimo){
		if(e.nome != nome){	
			temp << e.nome << " " << e.emprestimo << endl;
		}
	}
	arquivo.close();
	temp.close();
	remove("livros.txt");
	rename("temp.txt", "livros.txt");
}

void in_al_ex(){
  int op;
  do{
    cout << "Opções:\n1 - Inserir livro\n2 - Alterar livro\n3 - Excluir livro\n0 - Sair\nDigite o número correspondente à opção desejada: ";
    cin >> op;
    switch (op) {
      case 1: {
        livro novo_livro;
        cout << "Inserir livro\n";
        inserir_livro(novo_livro);
        break;
      }

      case 2: {
        cout << "Alterar livro\n";
        alterar_livro();
        break;
      }

      case 3: {
        cout << "Excluir livro\n";
        excluir_livro();
        break;
      }
    }
  }while (op!=0);
}

void todos_emprestimos() {
  livro e;
  ifstream arquivo("livros.txt");
  while (arquivo >> e.nome >> e.emprestimo) {
    if (e.emprestimo != "0"){
      cout << "Livro: " << e.nome << " está com: " << e.emprestimo << "\n";
      }
  }
  arquivo.close();
}

void fazer_emprestimo() {
  livro e;
  cout << "Digite o nome do aluno: ";
  cin >> e.emprestimo;
  cout << "Digite o nome do livro: ";
  cin >> e.nome;

  string n, m;
  ifstream livros("livros.txt");
  ofstream temp("temp.txt");
  while (livros >> n >> m) {
    if (n == e.nome) {
      temp << n << " " << e.emprestimo << "\n";
    }
    else {
      temp << n << " " << m << "\n";
    }
  }
  livros.close();
	temp.close();
	remove("livros.txt");
	rename("temp.txt", "livros.txt");	
}

void todos_usuarios() {
  usuario u;
  ifstream arquivo("usuarios.txt");
  while (arquivo >> u.nome >> u.senha >> u.permissao) {
    cout << u.nome << endl;
  }
  arquivo.close();
}

void inserir_usuario() {
  usuario novo;
  cout << "Digite o nome do novo usuário: ";
  cin >> novo.nome;
  cout << "Digite a senha do novo usuário: ";
  cin >> novo.senha;
  cout << "Digite o número correspondente à permissão do novo usuário (1 - Aluno | 2 - Funcionário | 3 - Administrador): ";
  cin >> novo.permissao;

  ofstream arquivo("usuarios.txt", ios::app);
  arquivo << novo.nome << " " << novo.senha << " " << novo.permissao << "\n";
  arquivo.close();
}

void editar_usuario() {
  ifstream arquivo("usuarios.txt");
	if(!arquivo.is_open()){
		cout << "Falha ao abrir ao abrir o arquivo" << endl;
		return;
	}

  string nome;
  cout << "Digite o nome do usuário que deseja alterar: ";
  cin >> nome;
	ofstream temp("temp.txt");
  string novo_nome, nova_senha;
  int nova_permissao;
	usuario u;
	while(arquivo >> u.nome >> u.senha >> u.permissao){
		if(u.nome == nome){
      cout << "Digite o novo nome de usuário: ";
      cin >> novo_nome;
      cout << "Digite a nova senha: ";
      cin >> nova_senha;
      cout << "Digite o número correspondente à nova permissão (1 - Aluno | 2 - Funcionário | 3 - Administrador): ";
      cin >> nova_permissao;
			temp << novo_nome << " " << nova_senha << " " << nova_permissao << endl;
		}
		else{
			temp << u.nome << " " << u.senha << " " << u.permissao << endl;
		}
	}
	arquivo.close();
	temp.close();
	remove("usuarios.txt");
	rename("temp.txt", "usuarios.txt");
}

void excluir_usuario() {
  ifstream arquivo("usuarios.txt");
	if(!arquivo.is_open()){
		cout << "Falha ao abrir ao abrir o arquivo" << endl;
		return;
	}

  string nome;
  cout << "Digite o nome do usuário que deseja excluir: ";
  cin >> nome;
	ofstream temp("temp.txt");
	usuario u;
	while(arquivo >> u.nome >> u.senha >> u.permissao){
		if(u.nome != nome){	
			temp << u.nome << " " << u.senha << " " << u.permissao << endl;
		}
	}
	arquivo.close();
	temp.close();
	remove("usuarios.txt");
	rename("temp.txt", "usuarios.txt");
}

int main() {
  int permissao;
  permissao = login();

  switch (permissao) {
    case 1: {
      int op;
      do {
        cout << "\nAluno\n1 - Ver todos livros cadastrados\n2 - Buscar um livro\n3 - Ver seus livros emprestados\n0 - Sair\nEscolha a opção desejada: ";
        cin >> op;
        switch (op) {
          case 1: {
            cout << "\nOpção selecionada: 1 - Ver todos livros cadastrados\n";
            ver_livros();
            break;
          }

          case 2: {
            cout << "\nOpção selecionada: 2 - Buscar um livro\n";
            buscar_livro();
            break;
          }

          case 3: {
            livro emprestimo;
            cout << "\nOpção selecionada: 3 - Ver seus livros emprestados\n";
            ver_emprestimos(emprestimo);
            break;
          }

          case 0: {
            cout << "\nFim do programa.";
            break;
          }

          default: {
            cout << "\nOpção inválida.\n";
            break;
          }
        }
      } while (op != 0);
      break;
    }

    case 2: {
      int op;
      do {
        cout << "\nFuncionário\n1 - Ver todos livros cadastrados\n2 - Buscar um livro\n3 - Inserir, alterar, ou excluir livro\n4 - Ver todos os empréstimos\n5 - Fazer empréstimo de livro\n0 - Sair\nEscolha a opção desejada: ";
        cin >> op;
        switch (op) {
          case 1: {
            cout << "\nOpção selecionada: 1 - Ver todos livros cadastrados\n";
            ver_livros();
            break;
          }

          case 2: {
            cout << "\nOpção selecionada: 2 - Buscar um livro\n";
            buscar_livro();
            break;
          }

          case 3: {
            cout << "\nOpção selecionada: 3 - Inserir, alterar, ou excluir livro\n";
            in_al_ex();
            break;
          }

          case 4: {
            cout << "\nOpção selecionada: 4 - Ver todos os empréstimos\n";
            todos_emprestimos();
            break;
          }

          case 5: {
            cout << "\nOpção selecionada: 5 - Fazer empréstimo de livro\n";
            fazer_emprestimo();
            break;
          }

          case 0: {
            cout << "\nFim do programa.";
            break;
          }

          default: {
            cout << "\nOpção inválida.\n";
            break;
          }
        }
      } while (op != 0);
      break;
    }

    case 3: {
      int op;
      do {
        cout << "\nAdministrador\n1 - Listar todos usuários\n2 - Inserir usuários\n3 - Editar usuários\n4 - Excluir usuários\n0 - Sair\nEscolha a opção desejada: ";
        cin >> op;
        switch (op) {
          case 1: {
            cout << "\nOpção selecionada: 1 - Listar todos usuários\n";
            todos_usuarios();
            break;
          }

          case 2: {
            cout << "\nOpção selecionada: 2 - Inserir usuários\n";
            inserir_usuario();
            break;
          }

          case 3: {
            cout << "\nOpção selecionada: 3 - Editar usuários\n";
            editar_usuario();
            break;
          }

          case 4: {
            cout << "\nOpção selecionada: 4 - Excluir usuários\n";
            excluir_usuario();
            break;
          }

          case 0: {
            cout << "\nFim do programa.";
            break;
          }

          default: {
            cout << "\nOpção inválida.\n";
            break;
          }
        }
      } while (op != 0);
      break;
    }

    default: {
      cout << "\nOpção inválida.\n";
      break;
    }
  }
}
