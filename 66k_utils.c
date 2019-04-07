#include "66k_utils.h"
/* Put in Utility File
*/

// Deal with _dequeue
// 	_dout get_label

typedef struct {
	const char * name;
	ut8 offset;
} _66207Reg;

static _66207Reg SFR[] = {
	{"ASSP", 0x0}, {"SSPH", 0x1}, 
	{"ALRB", 0x2}, {"LRBH", 0x3}, 
	{"PSW", 0x4}, {"zp_PSWH", 0x5}, 
	{"ACC", 0x6}, {"ACCH", 0x7}, 
	{"SBYCON", 0x10}, {"WDT", 0x11}, 
	{"PRPHF", 0x12}, {"STPACP", 0x13}, 
	{"IRQ", 0x18}, {"IRQH", 0x19}, 
	{"IE", 0x1a}, {"IEH", 0x1b}, {"EXION", 0x1c}, 
	{"P0", 0x20}, {"P0IO", 0x21}, {"P1", 0x22}, {"P1IO", 0x23}, 
	{"P2", 0x24}, {"P2IO", 0x25}, {"P2SF", 0x26}, 
	{"P3", 0x28}, {"P3IO", 0x29}, {"P3SF", 0x2a}, 
	{"P4", 0x2c}, {"P4IO", 0x2d}, {"P4SF", 0x2e}, 
	{"P5", 0x2f}, 
	{"TM0", 0x30}, {"TM0H", 0x31}, {"TMR0", 0x32}, {"TMR0H", 0x33}, 
	{"TM1", 0x34}, {"TM1H", 0x35}, {"TMR1", 0x36}, {"TMR1H", 0x37}, 
	{"TM2", 0x38}, {"TM2H", 0x39}, {"TMR2", 0x3a}, {"TMR2H", 0x3b}, 
	{"TM3", 0x3c}, {"TM3H", 0x3d}, {"TMR3", 0x3e}, {"TMR3H", 0x3f}, 
	{"TCON0", 0x40}, {"TCON1", 0x41}, {"TCON2", 0x42}, {"TCON3", 0x43}, 
	{"TRNSIT", 0x46}, 
	{"STTM", 0x48}, {"STTMR", 0x49}, {"STTMC", 0x4a}, 
	{"SRTM", 0x4c}, {"SRTMR", 0x4d}, {"SRTMC", 0x4e}, 
	{"STCON", 0x50}, {"STBUF", 0x51}, 
	{"SRCON", 0x54}, {"SRBUF", 0x55}, {"SRSTAT", 0x56}, 
	{"ADSCAN", 0x58}, {"ADSEL", 0x59}, 
	{"ADCR0", 0x60}, {"ADCR0H", 0x61}, {"ADCR1", 0x62}, {"ADCR1H", 0x63}, 
	{"ADCR2", 0x64}, {"ADCR2H", 0x65}, {"ADCR3", 0x66}, {"ADCR3H", 0x67}, 
	{"ADCR4", 0x68}, {"ADCR4H", 0x69}, {"ADCR5", 0x6a}, {"ADCR5H", 0x6b}, 
	{"ADCR6", 0x6c}, {"ADCR6H", 0x6d}, {"ADCR7", 0x6e}, {"ADCR7H", 0x6f}, 
	{"PWMC0", 0x70}, {"PWMC0H", 0x71}, {"PWMR0", 0x72}, {"PWMR0H", 0x73}, 
	{"PWMC1", 0x74}, {"PWMC1H", 0x75}, {"PWMR1", 0x76}, {"PWMR1H", 0x77}, 
	{"PWCON0", 0x78}, 
	{"PWCON1", 0x7a}
};


static int _66207_reg_compare(const void *addr, const void *reg) {
	return (*(const ut8*)addr) - (((_66207Reg*)reg)->offset);
}

static _66207Reg *_66207_reg_find(unsigned addr) {
	return (_66207Reg *) bsearch (
		&addr, SFR,
		sizeof (SFR) / sizeof (SFR[0]),
		sizeof (SFR[0]),
		_66207_reg_compare);
}

/* Debug print func */
void dp(char* str) {
        char* debugfile = "/tmp/66k_disas.log";
        FILE* fp = fopen(debugfile, "a");
        if(fp == NULL)
                return;

        fprintf(fp, str);
        fclose(fp);
}

const char *get_rom_label(unsigned addr)
{
	char debugprintbuf[256];
	snprintf(debugprintbuf, 256, "Got Address %04x ", addr);
	dp(debugprintbuf);

	// MALLOC FOR NOW
	// Later make global var to free variable	
	static char hex[10]; //=  malloc(sizeof(char)*10);
	sprintf(hex, "0x%04x", addr);
	
	return hex;
}


// deal with dout

// 	dout getlabel
//      dout addlabel
// NOT C CONVERT
/*
void DASMOutput::add_label(unsigned addr, const string &l) 
{
        if(lines.find(addr*4+1) == lines.end())
                lines.insert(pair<unsigned,string>(addr*4+1,l));
}
*/
/*
const char *DASMOutput::get_label(unsigned addr)
{
	
        multimap<unsigned,string>::iterator i;
        i = lines.find(addr*4+1);
        if(i == lines.end())
                return NULL;
        return (*i).second.c_str();
	
	const char hex[10];
	sprintf(hex, "%x", addr);
	return hex;
}
*/
const char *get_romtable_label(unsigned addr)
{

        static char lbuf[64];
/*
        static char *lbuf=lbuf2;
        lbuf = (lbuf == lbuf1) ? lbuf2 : lbuf1;
        if(!_dout->ignore(addr) &&  
                        (addr >= tbladdr_lo && addr < tbladdr_hi)) {
                const char *l = _dout->get_label(addr);
                if(l) return l;
                sprintf(lbuf, "tbl_%04x", addr);
                _dout->add_label(addr, lbuf);
                return lbuf;
        }   
        sprintf(lbuf, "0%04xh", addr);
        return lbuf;
*/
        sprintf(lbuf, "0%04xh", addr);
        return lbuf;
}



//static map<unsigned, const char *> _SFRs;
const char *get_ram_label(unsigned addr, int digits)
{
 
	static char lbuf[64];
/*
        static char *lbuf=lbuf2;
        lbuf = (lbuf == lbuf1) ? lbuf2 : lbuf1;
        map<unsigned, const char *>::iterator i =
                _SFRs.find(addr);
*/   

	// USE BSEARCH TO HUNT REGISTER
        _66207Reg * resolved = _66207_reg_find(addr);
	if (resolved != NULL){	
		return (const char *) resolved->name;
	}else{
		sprintf(lbuf, "0%0*xh", digits, addr);
		return lbuf;
	}
		
}


const unsigned vcal_base=0x28;
void do_vcal(unsigned n)
{
	/*
        unsigned addr = _D->rom[vcal_base+n*2]|(_D->rom[vcal_base+n*2+1]<<8);
        get_rom_label(addr);
	*/
	int i = 0;
}


