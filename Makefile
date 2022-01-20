# md5calc Makefile
TARGET = md5calc

CFLAGS = -O2 -Wall -Wextra
LDFLAGS = -Wl,--no-undefined # as i remember, this is gcc only

OBJS =  md5.o \
	get_md5.o \
	main.o

ifdef STATIC
	LDFLAGS += -static
endif

DOCC = $(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
DOO = $(CC) -o $@ $(OBJS) $(LDFLAGS)

all: $(TARGET)

$(TARGET): $(OBJS)
		$(DOO)

./%.o: ./%.c
		$(DOCC)

clean:
		@rm -f $(OBJS) $(TARGET)
