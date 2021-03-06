CONFIG += c++11

INCLUDEPATH += \
	$$PWD/include/ \
	$$PWD/../thirdparty/ \
	$$PWD/.. \

LIBS += -L$$PWD/../bin -lqrkernel -lqslog

DEFINES += QRTEXT_LIBRARY

TRANSLATIONS = $$PWD/../qrtranslations/ru/qrtext_ru.ts

HEADERS += \
	$$PWD/include/qrtext/debuggerInterface.h \
	$$PWD/include/qrtext/declSpec.h \
	$$PWD/include/qrtext/languageToolboxInterface.h \
	$$PWD/include/qrtext/core/error.h \
	$$PWD/include/qrtext/core/connection.h \
	$$PWD/include/qrtext/core/range.h \
	$$PWD/include/qrtext/core/ast/node.h \
	$$PWD/include/qrtext/core/ast/expression.h \
	$$PWD/include/qrtext/core/ast/binaryOperator.h \
	$$PWD/include/qrtext/core/ast/unaryOperator.h \
	$$PWD/include/qrtext/core/lexer/lexer.h \
	$$PWD/include/qrtext/core/lexer/token.h \
	$$PWD/include/qrtext/core/lexer/tokenPatterns.h \
	$$PWD/include/qrtext/core/parser/parser.h \
	$$PWD/include/qrtext/core/parser/parserContext.h \
	$$PWD/include/qrtext/core/parser/parserRef.h \
	$$PWD/include/qrtext/core/parser/tokenStream.h \
	$$PWD/include/qrtext/core/parser/precedenceTable.h \
	$$PWD/include/qrtext/core/parser/operators/parserCombinators.h \
	$$PWD/include/qrtext/core/parser/operators/tokenParser.h \
	$$PWD/include/qrtext/core/parser/operators/simpleParser.h \
	$$PWD/include/qrtext/core/parser/operators/parserInterface.h \
	$$PWD/include/qrtext/core/parser/operators/alternativeParser.h \
	$$PWD/include/qrtext/core/parser/operators/transformingParser.h \
	$$PWD/include/qrtext/core/parser/operators/concatenationParser.h \
	$$PWD/include/qrtext/core/parser/operators/optionalParser.h \
	$$PWD/include/qrtext/core/parser/operators/kleeneStarParser.h \
	$$PWD/include/qrtext/core/parser/operators/expressionParser.h \
	$$PWD/include/qrtext/core/parser/temporaryNodes/temporaryDiscardableNode.h \
	$$PWD/include/qrtext/core/parser/temporaryNodes/temporaryList.h \
	$$PWD/include/qrtext/core/parser/temporaryNodes/temporaryPair.h \
	$$PWD/include/qrtext/core/parser/temporaryNodes/temporaryToken.h \
	$$PWD/include/qrtext/core/parser/utils/functionTraits.h \
	$$PWD/include/qrtext/core/semantics/semanticAnalyzer.h \
	$$PWD/include/qrtext/core/semantics/generalizationsTableInterface.h \
	$$PWD/include/qrtext/core/types/any.h \
	$$PWD/include/qrtext/core/types/typeExpression.h \
	$$PWD/include/qrtext/core/types/typeVariable.h \
	$$PWD/include/qrtext/lua/luaToolbox.h \
	$$PWD/include/qrtext/lua/ast/number.h \
	$$PWD/include/qrtext/lua/ast/unaryMinus.h \
	$$PWD/include/qrtext/lua/ast/not.h \
	$$PWD/include/qrtext/lua/ast/node.h \
	$$PWD/include/qrtext/lua/ast/expression.h \
	$$PWD/include/qrtext/lua/ast/binaryOperator.h \
	$$PWD/include/qrtext/lua/ast/unaryOperator.h \
	$$PWD/include/qrtext/lua/ast/bitwiseNegation.h \
	$$PWD/include/qrtext/lua/ast/length.h \
	$$PWD/include/qrtext/lua/ast/logicalAnd.h \
	$$PWD/include/qrtext/lua/ast/logicalOr.h \
	$$PWD/include/qrtext/lua/ast/addition.h \
	$$PWD/include/qrtext/lua/ast/subtraction.h \
	$$PWD/include/qrtext/lua/ast/multiplication.h \
	$$PWD/include/qrtext/lua/ast/division.h \
	$$PWD/include/qrtext/lua/ast/integerDivision.h \
	$$PWD/include/qrtext/lua/ast/modulo.h \
	$$PWD/include/qrtext/lua/ast/exponentiation.h \
	$$PWD/include/qrtext/lua/ast/bitwiseAnd.h \
	$$PWD/include/qrtext/lua/ast/bitwiseOr.h \
	$$PWD/include/qrtext/lua/ast/bitwiseXor.h \
	$$PWD/include/qrtext/lua/ast/bitwiseLeftShift.h \
	$$PWD/include/qrtext/lua/ast/bitwiseRightShift.h \
	$$PWD/include/qrtext/lua/ast/concatenation.h \
	$$PWD/include/qrtext/lua/ast/equality.h \
	$$PWD/include/qrtext/lua/ast/lessThan.h \
	$$PWD/include/qrtext/lua/ast/lessOrEqual.h \
	$$PWD/include/qrtext/lua/ast/inequality.h \
	$$PWD/include/qrtext/lua/ast/greaterThan.h \
	$$PWD/include/qrtext/lua/ast/greaterOrEqual.h \
	$$PWD/include/qrtext/lua/ast/integerNumber.h \
	$$PWD/include/qrtext/lua/ast/floatNumber.h \
	$$PWD/include/qrtext/lua/ast/fieldInitialization.h \
	$$PWD/include/qrtext/lua/ast/tableConstructor.h \
	$$PWD/include/qrtext/lua/ast/integerNumber.h \
	$$PWD/include/qrtext/lua/ast/floatNumber.h \
	$$PWD/include/qrtext/lua/ast/string.h \
	$$PWD/include/qrtext/lua/ast/true.h \
	$$PWD/include/qrtext/lua/ast/false.h \
	$$PWD/include/qrtext/lua/ast/nil.h \
	$$PWD/include/qrtext/lua/ast/identifier.h \
	$$PWD/include/qrtext/lua/ast/functionCall.h \
	$$PWD/include/qrtext/lua/ast/methodCall.h \
	$$PWD/include/qrtext/lua/ast/assignment.h \
	$$PWD/include/qrtext/lua/ast/block.h \
	$$PWD/include/qrtext/lua/ast/indexingExpression.h \
	$$PWD/include/qrtext/lua/types/boolean.h \
	$$PWD/include/qrtext/lua/types/float.h \
	$$PWD/include/qrtext/lua/types/function.h \
	$$PWD/include/qrtext/lua/types/integer.h \
	$$PWD/include/qrtext/lua/types/nil.h \
	$$PWD/include/qrtext/lua/types/number.h \
	$$PWD/include/qrtext/lua/types/string.h \
	$$PWD/include/qrtext/lua/types/table.h \
	$$PWD/src/lua/luaGeneralizationsTable.h \
	$$PWD/src/lua/luaInterpreter.h \
	$$PWD/src/lua/luaLexer.h \
	$$PWD/src/lua/luaParser.h \
	$$PWD/src/lua/luaPrecedenceTable.h \
	$$PWD/src/lua/luaSemanticAnalyzer.h \
	$$PWD/src/lua/luaTokenTypes.h \

SOURCES += \
	$$PWD/src/core/connection.cpp \
	$$PWD/src/core/error.cpp \
	$$PWD/src/core/range.cpp \
	$$PWD/src/core/ast/node.cpp \
	$$PWD/src/core/semantics/semanticAnalyzer.cpp \
	$$PWD/src/core/types/typeVariable.cpp \
	$$PWD/src/lua/luaGeneralizationsTable.cpp \
	$$PWD/src/lua/luaInterpreter.cpp \
	$$PWD/src/lua/luaLexer.cpp \
	$$PWD/src/lua/luaParser.cpp \
	$$PWD/src/lua/luaPrecedenceTable.cpp \
	$$PWD/src/lua/luaSemanticAnalyzer.cpp \
	$$PWD/src/lua/luaToolbox.cpp \
