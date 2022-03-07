PYTHON3=python3

default: autocoder/ fsw/
	$(PYTHON3) ./autocoder/build_all.py build_config.json

clean:
	rm -rf /tmp/autocps_fsw.*
