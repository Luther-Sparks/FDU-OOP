help:
	@echo "Usage: make [target]"
	@echo "Available targets: welcome clean"

stop:
ifneq ($(OS),Windows_NT)
	@echo "Stop the music"
	@pkill afplay || true
endif

.PHONY: clean
clean:
	@cd lib && make -s clean
	@cd game && make -s clean
	@cd task1 && make -s clean
	@cd task2 && make -s clean