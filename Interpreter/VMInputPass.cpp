#include "VMInputPass.h"


void  VMInputPass::test()
{
	literal a;

	a.number = 6;

	expression* aExp = (expression*)malloc(sizeof(expression));

	*aExp = initLiteralExpression(a);

	literal b;

	b.number = 7;

	expression* bExp = (expression*)malloc(sizeof(expression));

	*bExp = initLiteralExpression(b);

	BinOp* result = makeBinOp(ADD, aExp, bExp);

	expression res = initBinOpExpression(result);

	if (res.kind == EXPR_BIN)
		cout << res.val.binaryOp.lhs->val.litVal.number << " + " << res.val.binaryOp.rhs->val.litVal.number << endl;

}