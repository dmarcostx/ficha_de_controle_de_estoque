/* Ficha de Controle de Estoque com desconto de ICMS
 * Autor: Marcos Vin�cius Louren�o Teixeira
 * Esse software � um trabalho escolar
 * Docente: Renato Ribeiro Soares
 * Disciplina: Contabilidade
 * Curso: Tecnologia em An�lise e Desenvolvimento de Sistemas
 * Per�odo: Noturno
 * Faculdade de Tecnologia � FATEC do Ipiranga "Pastor En�as Tognini"
 * Centro Paula Souza
 * Governo do Estado de S�o Paulo
 * Licen�a: Eu dedico todo e qualquer interesse por direitos autorais neste software para o dom�nio p�blico. Eu fa�o essa dedica��o para o benef�cio do p�blico em geral e em detrimento de meus herdeiros e sucessores. Eu pretendo que essa dedica��o seja um ato declarado de ren�ncia, em perpetuidade, a todos os direitos presentes e futuros a este software sob a lei de direitos autorais.
 * Garantia: O c�digo-fonte do software � fornecido no estado em que se encontra, sem nenhum tipo de garantia, expressa ou impl�cita, incluindo, mas n�o se limitando �s garantias de comercializa��o, adequa��o a um fim espec�fico e n�o viola��o. Em nenhuma circunst�ncia, os autores ser�o respons�veis por qualquer reinvindica��o, dano ou outras responsabilidades, seja em a��o de contrato, delito ou de outra forma, decorrentes de, ou em rela��o ao software ou � sua utiliza��o ou a outra aplica��o do software.
 */

#include <stdio.h>

struct saldo
{
	unsigned int qtd;
	double preco;
};

unsigned int saldo_total_UEPS(struct saldo *saldo, unsigned int proximo)
{
	int soma = 0;
	while (proximo > 0)
		soma += saldo[--proximo].qtd;
	return soma;
}

void compra_UEPS(struct saldo *operacao, unsigned int *proximo, double icms)
{
	printf("Quantidade: ");
	scanf("%u", &operacao->qtd);
	if (operacao->qtd == 0)
		return;
	printf("Preco: R$ ");
	scanf("%lf", &operacao->preco);
	operacao->preco = operacao->preco*icms/100;
	++(*proximo);
}

void venda_UEPS(struct saldo *saldo, unsigned int qtd, unsigned int *proximo)
{
	if (qtd > saldo_total_UEPS(saldo, *proximo))
		fprintf(stderr, "\nNao existe quantidade sulficiente em estoque para efetuar a venda!\n");
	else
	{
		if (saldo[*proximo - 1].qtd > qtd)
		{
			saldo[*proximo - 1].qtd -= qtd;
			printf("Preco: R$ %.2lf\n", saldo[*proximo - 1].preco);
		}
		else if (saldo[*proximo - 1].qtd == qtd)
			printf("Preco: R$ %.2lf\n", saldo[--(*proximo)].preco);
		else
		{
			printf("\nQuantidade: %u\n", saldo[--(*proximo)].qtd);
			printf("Preco: R$ %.2lf\n", saldo[*proximo].preco);
			qtd -= saldo[*proximo].qtd;
			printf("\nQuantidade: %u\n", qtd);
			venda_UEPS(saldo, qtd, proximo);
		}
	}
}

void print_UEPS(struct saldo *saldo, unsigned int proximo)
{
	struct saldo soma;
	soma.qtd = 0;
	soma.preco = 0;
	for (unsigned int i = 0; i < proximo; i++)
	{
		printf("\nQuantidade: %u\nPreco: R$ %.2lf\n", saldo[i].qtd, saldo[i].preco);
		soma.qtd += saldo[i].qtd;
		soma.preco += saldo[i].preco;
	}
	printf("\nQuantidade total: %u\nPreco total: R$ %.2lf\n", soma.qtd, soma.preco);
}

unsigned int saldo_total_PEPS(struct saldo *saldo, unsigned int primeiro, unsigned int proximo)
{
	unsigned int soma = 0;
	while (proximo > primeiro)
		soma += saldo[--proximo].qtd;
	return soma;
}

void venda_PEPS(struct saldo *saldo, unsigned int qtd, unsigned int *primeiro, unsigned int *proximo)
{
	if (qtd > saldo_total_PEPS(saldo, *primeiro, *proximo))
		fprintf(stderr, "\nNao existe quantidade sulficiente em estoque para efetuar a venda!\n");
	else
	{
		if (saldo[*primeiro].qtd > qtd)
		{
			saldo[*primeiro].qtd -= qtd;
			printf("Preco: R$ %.2lf\n", saldo[*primeiro].preco);
		}
		else if (saldo[*primeiro].qtd == qtd)
		{
			printf("Preco: R$ %.2lf\n", saldo[*primeiro].preco);
			++(*primeiro);
		}
		else
		{
			printf("\nQuantidade: %u\n", saldo[*primeiro].qtd);
			printf("Preco: R$ %.2lf\n", saldo[*primeiro].preco);
			qtd -= saldo[*primeiro].qtd;
			printf("\nQuantidade: %u\n", qtd);
			++(*primeiro);
			venda_PEPS(saldo, qtd, primeiro, proximo);
		}
	}
}

void print_PEPS(struct saldo *saldo, unsigned int primeiro, unsigned int proximo)
{
	struct saldo soma;
	soma.qtd = 0;
	for (soma.preco = 0; primeiro < proximo; primeiro++)
	{
		printf("\nQuantidade: %u\nPreco: R$ %.2lf\n", saldo[primeiro].qtd, saldo[primeiro].preco);
		soma.qtd += saldo[primeiro].qtd;
		soma.preco += saldo[primeiro].preco;
	}
	printf("\nQuantidade total: %u\nPreco total: R$ %.2lf\n", soma.qtd, soma.preco);
}

void compra_CMP(struct saldo *saldo, double icms)
{
	struct saldo operacao;
	printf("Quantidade: ");
	scanf("%u", &operacao.qtd);
	if (operacao.qtd < 1)
		return;
	printf("Preco: R$ ");
	scanf("%lf", &operacao.preco);
	operacao.preco = operacao.preco*icms/100;
	saldo->preco = (saldo->qtd * saldo->preco + operacao.qtd * operacao.preco) / (saldo->qtd + operacao.qtd);
	saldo->qtd += operacao.qtd;
}

void venda_CMP(struct saldo *saldo, unsigned int qtd)
{
	if (qtd > saldo->qtd)
		fprintf(stderr, "\nNao existe quantidade sulficiente em estoque para efetuar a venda!\n");
	else
	{
		saldo->qtd -= qtd;
		printf("Preco: R$ %.2lf\n", saldo->preco);
	}
}

void UEPS(double icms)
{
	struct saldo saldo[128];
	unsigned int proximo = 0, qtd;
	printf("\nEstoque Inicial:\n");
	compra_UEPS(&saldo[proximo], &proximo, 100);
	char menu;
	while (1)
	{
		printf("\nDigite C para inserir operacao de compra\n");
		printf("Digite V para inserir operacao de venda\n");
		printf("Digite S para exibir o saldo\n");
		printf(">");
		scanf(" %c", &menu);
		if (menu == 'C' || menu == 'c')
			compra_UEPS(&saldo[proximo], &proximo, icms);
		else if (menu == 'V' || menu == 'v')
		{
			printf("\nQuantidade: ");
			scanf("%u", &qtd);
			venda_UEPS(saldo, qtd, &proximo);
		}
		else if (menu == 'S' || menu == 's')
		{
			print_UEPS(saldo, proximo);
		}
		else
			break;
	}
}

void PEPS(double icms)
{
	struct saldo saldo[128];
	unsigned int primeiro = 0, proximo = 0, qtd;
	printf("\nEstoque Inicial:\n");
	compra_UEPS(&saldo[proximo], &proximo, 100);
	char menu;
	while (1)
	{
		printf("\nDigite C para inserir operacao de compra\n");
		printf("Digite V para inserir operacao de venda\n");
		printf("Digite S para exibir o saldo\n");
		printf(">");
		scanf(" %c", &menu);
		if (menu == 'C' || menu == 'c')
			compra_UEPS(&saldo[proximo], &proximo, icms);
		else if (menu == 'V' || menu == 'v')
		{
			printf("\nQuantidade: ");
			scanf("%u", &qtd);
			venda_PEPS(saldo, qtd, &primeiro, &proximo);
		}
		else if (menu == 'S' || menu == 's')
		{
			print_PEPS(saldo, primeiro, proximo);
		}
		else
			break;
	}
}

void CMP(double icms)
{
	struct saldo saldo;
	saldo.qtd = 0;
	unsigned int qtd;
	printf("\nEstoque Inicial:\n");
	compra_CMP(&saldo, 100);
	char menu;
	while (1)
	{
		printf("\nDigite C para inserir operacao de compra\n");
		printf("Digite V para inserir operacao de venda\n");
		printf("Digite S para exibir o saldo\n");
		printf(">");
		scanf(" %c", &menu);
		if (menu == 'C' || menu == 'c')
			compra_CMP(&saldo, icms);
		else if (menu == 'V' || menu == 'v')
		{
			printf("\nQuantidade: ");
			scanf("%u", &qtd);
			venda_CMP(&saldo, qtd);
		}
		else if (menu == 'S' || menu == 's')
		{
			printf("\nQuantidade total: %u\n", saldo.qtd);
			if (saldo.qtd > 0)
				printf("Preco total: R$ %.2lf\n", saldo.preco);
		}
		else
			break;
	}
}

int main()
{
	char menu;
	double icms;
	printf(" - Ficha de Controle de Estoque com desconto de ICMS -\n\n");
	printf("Aliquota do ICMS: ");
	scanf("%lf", &icms);
	icms = 100 - icms;
	printf("\nDigite U para UEPS\n");
	printf("Digite P para PEPS\n");
	printf("Digite C para CMP\n");
	printf(">");
	scanf(" %c", &menu);
	if (menu == 'U' || menu == 'u')
		UEPS(icms);
	else if (menu == 'P' || menu == 'p')
		PEPS(icms);
	else if (menu == 'C' || menu == 'c')
		CMP(icms);
	return 0;
}