##
# Project Title
#
.PHONY: project code test description presentation learn reunion

all: code test

pdf: description presentation learn reunion

project:
	cd code/build/ && make

code:
	cd code/build/ && make project && ./bin/project

test:
	cd code/build/ && make test && ./bin/test

doc:
	cd code/build/ && make doc
	firefox code/doc/html/index.html &

description:
	cd description/ && make project && make run &

presentation:
	cd dossier_presentation/ && make && evince dossier_presentation.pdf
	evince pdf_presentation/EIRBOT_DEFINITIF.pdf

learn:
	cd learn/ make git && make makefile
	evince learn/learn_git.pdf
	evince learn/learn_makefile.pdf

reunion:
	cd reunion/ && make project && make run

clean:
	cd code && make clean
	cd description && make clean
	cd dossier_presentation && make clean
	cd learn && make clean
	cd reunion && make clean

# end
