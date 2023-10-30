include ../../make_config.mk

ifndef DISABLE_JEMALLOC
	ifdef JEMALLOC
		PLATFORM_CXXFLAGS += "-DROCKSDB_JEMALLOC"
	endif
	EXEC_LDFLAGS := $(JEMALLOC_LIB) $(EXEC_LDFLAGS) -lpthread
	PLATFORM_CXXFLAGS += $(JEMALLOC_INCLUDE)
endif

.PHONY: clean librocksdb

all: cloud_durable_example clone_example cloud_dump cloud_restful

cloud_durable_example: librocksdb cloud_durable_example.cc
	$(CXX) $(CXXFLAGS) $@.cc -o $@ ../../librocksdb.a -I../../include $(OPT) -std=c++11 $(PLATFORM_LDFLAGS) $(PLATFORM_CXXFLAGS) $(EXEC_LDFLAGS)

clone_example: librocksdb clone_example.cc
	$(CXX) $(CXXFLAGS) $@.cc -o $@ ../../librocksdb.a -I../../include $(OPT) -std=c++11 $(PLATFORM_LDFLAGS) $(PLATFORM_CXXFLAGS) $(EXEC_LDFLAGS)

cloud_dump: librocksdb cloud_dump.cc
	$(CXX) $(CXXFLAGS) $@.cc -o $@ ../../librocksdb.a -I../../include $(OPT) -std=c++11 $(PLATFORM_LDFLAGS) $(PLATFORM_CXXFLAGS) $(EXEC_LDFLAGS)

cloud_restful: librocksdb cloud_restful.cc
	$(CXX) $(CXXFLAGS) $@.cc -o $@ ../../librocksdb.a -I../../include $(OPT) -std=c++11 $(PLATFORM_LDFLAGS) $(PLATFORM_CXXFLAGS) $(EXEC_LDFLAGS) -lboost_system

clean:
	rm -rf ./cloud_durable_example  ./clone_example ./cloud_dump ./cloud_restful

librocksdb:
	cd ../.. && $(MAKE) static_lib
