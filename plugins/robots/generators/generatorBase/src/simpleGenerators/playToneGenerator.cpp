#include "playToneGenerator.h"
#include "generatorBase/generatorCustomizer.h"

using namespace generatorBase::simple;
using namespace qReal;

PlayToneGenerator::PlayToneGenerator(qrRepo::RepoApi const &repo
		, GeneratorCustomizer &customizer
		, Id const &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "playTone.t", QList<Binding *>()
			<< Binding::createConverting("@@FREQUENCY@@", "Frequency", customizer.factory()->intPropertyConverter())
			<< Binding::createConverting("@@DURATION@@", "Duration", customizer.factory()->intPropertyConverter())
			<< Binding::createConverting("@@VOLUME@@", "Volume", customizer.factory()->intPropertyConverter())
			, parent)
{
}
