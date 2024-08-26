# Grupo SO-024
# Afonso Santos - fc59808
# Madalena Machado - fc59858
# Liliana Valente - fc59846

CC = gcc
CFLAGS = -Wall -I $(INCLUDE_DIR)

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

EXEC_NAME = hOSpital

OBJS = main.o memory.o process.o receptionist.o patient.o doctor.o configuration.o hosptime.o hospsignal.o stats.o log.o synchronization.o

main.o = main.h
memory.o = memory.h
process.o = process.h
receptionist.o = receptionist.h
patient.o = patient.h
doctor.o = doctor.h
configuration.o = configuration.h
hosptime.o = hosptime.h
hospsignal.o = hospsignal.h
stats.o = stats.h 
log.o = log.h 
synchronization.o = synchronization.h

vpath %.o $(OBJ_DIR)
vpath %.c $(SRC_DIR)

$(BIN_DIR)/$(EXEC_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR)/,$(OBJS)) -o $@

%.o: %.c $($@)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/$@ -c $<

folders:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/$(EXEC_NAME)
