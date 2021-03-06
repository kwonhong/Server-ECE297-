# The storage client library.
CLIENTLIB = libstorage.a

# The programs to build.
TARGETS = $(CLIENTLIB) yaccer lexer server client encrypt_passwd 

# The source files.
SRCS = server.c storage.c utils.c client.c encrypt_passwd.c hashTable.c lex.yy.c config_parser.tab.c 

# Compile flags.
CFLAGS = -g -Wall
LDFLAGS = -g -Wall -lcrypt -lpthread

# Dependencies file
DEPEND_FILE = depend.mk

LEX = flex
YACC = bison

# ---------------------------------------------------------
# Targets to build the storage client and server.
# ---------------------------------------------------------

# Default targets.
build: $(TARGETS)

# Build the client library.
$(CLIENTLIB): storage.o utils.o config_parser.tab.o lex.yy.o
	$(AR) rcs $@ $^

# Build the server.
server: server.o utils.o hashTable.o parser
	echo "Start server compilation"
	$(CC) $(LDFLAGS) server.o utils.o hashTable.o lex.yy.o config_parser.tab.o -o $@

# Build the client.
client: client.o  $(CLIENTLIB)
	$(CC) $(LDFLAGS) $^ -o $@

# Build the password encryptor.
encrypt_passwd: encrypt_passwd.o utils.o
	$(CC) $(LDFLAGS) $^ -o $@


lexer: config_parser.l
	${LEX} config_parser.l
	${CC} ${CFLAGS} ${INCLUDE} -c lex.yy.c

yaccer: config_parser.y
	${YACC} -d config_parser.y
	${CC} ${CFLAGS} ${INCLUDE} -c config_parser.tab.c

parser: lexer yaccer
#parser: config_parser.tab.o lex.yy.o
#	${CC} ${CFLAGS} ${INCLUDE} -c parser.c
#	${CC} -o p ${CFLAGS} ${INCLUDE} lex.yy.o config_parser.tab.o parser.o



# Compile a .c source file to a .o object file.
%.o: %.c
	$(CC) $(CFLAGS) -lpthread -c $< -o $@

# Delete generated files.
clean:
	-rm -rf $(TARGETS) *.o tags $(DEPEND_FILE)

# Create dependencies file.
depend:
	$(CC) $(CFLAGS) -M $(SRCS) > $(DEPEND_FILE)

-include $(DEPEND_FILE)


# ---------------------------------------------------------
# Targets to help work with the code.
# ---------------------------------------------------------

# Create tags file to help with code navigation in some editors.
tags: *.c *.h
	ctags -R .

# Create tags file including system header files.
fulltags: *.c *.h
	ctags -R . `$(MAKE) -s print_include_dirs`

# Print the include directories for current system.
print_include_dirs:
	@gcc -x c -Wp,-v -E - < /dev/null 2>&1 |grep '^ '

.PHONY: build depend clean tags fulltags print_include_dirs



