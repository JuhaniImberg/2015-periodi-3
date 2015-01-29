.PHONY: pandoc

%.pdf: %.md
	pandoc -t latex -o $@ $*.md

all: pandoc

pandoc: specification.pdf week1.pdf week2.pdf

clean:
	rm *.pdf
