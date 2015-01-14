.PHONY: pandoc

%.pdf: %.md
	pandoc -t latex -o $@ $*.md

all: pandoc

pandoc: specification.pdf

clean:
	rm *.pdf
