BUNDLE = lv2pftci-sampleRateReducerMUS.lv2
INSTALL_DIR = /usr/local/lib/lv2

$(BUNDLE): manifest.ttl sampleRateReducerMUS.ttl sampleRateReducerMUS.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp manifest.ttl sampleRateReducerMUS.ttl sampleRateReducerMUS.so $(BUNDLE)

sampleRateReducerMUS.so: sampleRateReducerMUS.cpp
	g++ -shared -fPIC -DPIC sampleRateReducerMUS.cpp `pkg-config --cflags --libs lv2-plugin` -o sampleRateReducerMUS.so

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)

clean:
	rm -rf $(BUNDLE) sampleRateReducerMUS.so
