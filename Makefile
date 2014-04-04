# makefile script by wangbangxu@makepolo.com

# global paths.
preprocessor_path=../../
boost_path=/usr/local/
libxml2_path=/usr/local/

# module paths.
src_path=src
obj_path=obj
lib_path=lib
lib_file=$(lib_path)/libsi.a

# cmd defines.
cc=g++
cflags=-O2 -g -Wall -fPIC

includes=-I ./src/ \
                 -I $(libxml2_path)/include/libxml2/ \
                 -I $(boost_path)/include/boost/ \

libs=$(lib_file) \
         -L $(libxml2_path)/lib -lxml2 \
         -L $(libxml2_path)/lib -lboost_date_time \
         -lpthread \
         -lz \

srcs=$(wildcard $(src_path)/*.cpp)
objs=$(patsubst $(src_path)/%.cpp, $(obj_path)/%.o, $(srcs))
bins=testsi

all:create_directory $(lib_file) $(bins)

$(lib_file): $(objs)
        ar r $@ $^

create_directory:
        mkdir -p $(obj_path) $(lib_path)

clean:
        rm -rf $(obj_path) $(lib_path) *.o $(bins)

rebuild: clean all

$(obj_path)/%.o:$(src_path)/%.cpp
        $(cc) -c $< $(cflags) -o $@ $(includes)
%.o:%.cpp
        $(cc) -c $< $(cflags) -o $@ $(includes)
testsi:testsi.o
        $(cc) -o $@ $^ $(includes) $(libs)
