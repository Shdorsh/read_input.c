# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abredimu <abredimu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/29 04:41:03 by shdorsh           #+#    #+#              #
#    Updated: 2024/12/30 11:15:56 by abredimu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = read_input.c
OBJ = $(SRC:.c=.o)
TARGET = read_input
MAIN_TARGET = main_target.o

CC = gcc
CFLAGS = -Wextra -Werror -Wall

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

so: $(OBJ)
	$(CC) $(CFLAGS) -shared -fPIC $(OBJ) -o lib$(TARGET).so

a: $(OBJ)
	$(CC) $(CFLAGS) -r $(OBJ) -o lib$(TARGET).a

main: $()
	$(CC) $(CFLAGS) $(OBJ) -o $(MAIN_TARGET)

clean:
	rm -rf $(OBJ) $(TARGET).o lib$(TARGET).so $(TARGET).S $(MAIN_TARGET)

.PHONY: so a asm clean main
