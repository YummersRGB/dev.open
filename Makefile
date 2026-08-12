ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. Example: export DEVKITPPC=/opt/devkitpro/devkitPPC")
endif

include $(DEVKITPPC)/wii_rules

TARGET   := dev/boot
BUILD    := build
SOURCES  := src

CFLAGS   := -O2 -Wall $(MACHDEP)
LDFLAGS  := $(MACHDEP) -mrvl -mcpu=750 -meabi -mhard-float -Wl,-Map,$(BUILD)/$(TARGET).map
LIBS     := -lwiiuse -lbongo -ldb -logc -lm

CFILES   := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
OBJS     := $(addprefix $(BUILD)/,$(CFILES:.c=.o))

all: dev/boot.dol

$(BUILD)/%.o: src/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

dev/boot.elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@

dev/boot.dol: dev/boot.elf
	elf2dol $< $@

clean:
	rm -rf $(BUILD) dev/boot.elf dev/boot.dol