# Executable names:
EXE = music
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o read_data.o graph.o draw_graph.o force_direct_graph.o force_direct_node.o Dijkstra.o

include cs225/make/cs225.mk

DATA_FILE=data/train.tsv

fetch_data:
ifeq ("$(wildcard $(DATA_FILE))","")
	curl -O https://zenodo.org/record/2553414/files/acousticbrainz-mediaeval-tagtraum-train.tsv.bz2 && bzip2 -d acousticbrainz-mediaeval-tagtraum-train.tsv.bz2 && mv acousticbrainz-mediaeval-tagtraum-train.tsv data/train.tsv
endif	
