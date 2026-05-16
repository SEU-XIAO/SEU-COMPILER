#include <cstdarg>
#include "yaccUtil.h"

#include "yaccParser.h"

#include "LRTable.h"

#include "yyWrite.h"

#include "yaccSource.h"

using namespace std;

static int printToStdout(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	return 0;
}

int main(int argc, char* argv[]) {

	const char* inputFile = (argc > 1) ? argv[1] : "SysY.y";
	YaccParser yyy(inputFile);

	dumpProducers(printToStdout);

	//printf("%s\n", YyWrite::make_init().c_str());

	yyy.writeTabs("y.tab.h");

	LRDFA dfa;
	dfa.generateLALR();

	LRTable lrt(dfa);

	//lrt.dump(printf);
	//printf("%s", lrt.code_dump("state", "c").c_str());

	(void)freopen("y.tab.c", "w", stdout);

	printf("%s\n", yacc_program.c_str());
	printf("void init_producers() { %s }\n", YyWrite::make_init().c_str());
	printf("int GoTo(int state, int c) { %s }\n", lrt.code_dump("state", "c").c_str());

	 
	return 0;
}