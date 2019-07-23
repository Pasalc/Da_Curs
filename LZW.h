#pragma once
#include "Compressor.h"
#include "TPrefix.h"

enum Borders {
	LOW_BORDER		=	10000,
	MEDIUM_BORDER	=	100000000000LLU,
	HIGH_BORDER		=	256204778801521550LLU
};

enum VariousDividers {
	LOW_FAST 		= 	100, 
	LOW_MEDIUM		= 	10,
	MEDIUM_FAST		= 	1000000,
	MEDIUM_MEDIUM	= 	1000,
	HIGH_FAST		= 	1000000000000LLU,
	HIGH_MEDIUM		= 	1000000
};

class TLZW: public ICompressor {
public:

	/* Конструктор класса
	 * передаваемое число определяет степень сжатия или говорит о декомпрессии
	 * */
	
	TLZW(int);

	/*	Имя: Compress
	 *	Что делает: Принимает решение о степени сжатия
	 */
	
	void Compress(std::string) override;

	/*	Имя: Decompress
	 *	Что делает: Расжимает данные
	 */
	
	void Decompress() override;

	~TLZW();

private:
	
	/* файл из которого осуществляется считывание */
	FILE forRead;
	
	/* основной файл для записи */
	FILE forWrite;
	
	/* Дерево компрессии */
	TPrefix* compressionTree;

	/*дерево декомрессии*/
	std::map<unsigned int, std::string> decompressionTree;
	
};
