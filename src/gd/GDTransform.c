#include <dolphin/gd/GDTransform.h>
#include <dolphin/os.h>
#include <macros.h>
#include "__gd.h"

void GDLoadPosMtxImm(MtxPtr mtx, u32 id)
{
  GDWriteXFCmdHdr(4 * id, 12);
  GDWrite_f32(mtx[0][0]);
  GDWrite_f32(mtx[0][1]);
  GDWrite_f32(mtx[0][2]);
  GDWrite_f32(mtx[0][3]);
  GDWrite_f32(mtx[1][0]);
  GDWrite_f32(mtx[1][1]);
  GDWrite_f32(mtx[1][2]);
  GDWrite_f32(mtx[1][3]);
  GDWrite_f32(mtx[2][0]);
  GDWrite_f32(mtx[2][1]);
  GDWrite_f32(mtx[2][2]);
  GDWrite_f32(mtx[2][3]);
}

void GDLoadPosMtxIndx(u16 mtx_indx, u32 id)
{
  GDWriteXFIndxACmd(4 * id, 12, mtx_indx);
}

void GDLoadNrmMtxImm(MtxPtr mtx, u32 id)
{
  GDWriteXFCmdHdr(id * 3 + 0x400, 9);
  GDWrite_f32(mtx[0][0]);
  GDWrite_f32(mtx[0][1]);
  GDWrite_f32(mtx[0][2]);
  GDWrite_f32(mtx[1][0]);
  GDWrite_f32(mtx[1][1]);
  GDWrite_f32(mtx[1][2]);
  GDWrite_f32(mtx[2][0]);
  GDWrite_f32(mtx[2][1]);
  GDWrite_f32(mtx[2][2]);
}

void GDLoadNrmMtxImm3x3(ROMtxPtr mtx, u32 id)
{
  GDWriteXFCmdHdr(id * 3 + 0x400, 9);
  GDWrite_f32(mtx[0][0]);
  GDWrite_f32(mtx[0][1]);
  GDWrite_f32(mtx[0][2]);
  GDWrite_f32(mtx[1][0]);
  GDWrite_f32(mtx[1][1]);
  GDWrite_f32(mtx[1][2]);
  GDWrite_f32(mtx[2][0]);
  GDWrite_f32(mtx[2][1]);
  GDWrite_f32(mtx[2][2]);
}

void GDLoadNrmMtxIndx3x3(u16 mtx_indx, u32 id)
{
	GDWriteXFIndxBCmd(id * 3 + 0x400, 9, mtx_indx);
}

void GDLoadTexMtxImm(MtxPtr mtx, u32 id, GXTexMtxType type)
{
	u16 addr;
	u8 count;

	if (id >= 0x40) {
		ASSERTMSGLINE(172, type == 0,
			"GDLoadTexMtxImm: invalid matrix type");

		addr = ((id - 0x40U & 0xffffffff) << 2) + 0x500;
		count = 12;
	} else {
		addr = 4 * id;
		count = type == 1 ? 8 : 12;
	}

	GDWriteXFCmdHdr(addr,count);
	GDWrite_f32(mtx[0][0]);
	GDWrite_f32(mtx[0][1]);
	GDWrite_f32(mtx[0][2]);
	GDWrite_f32(mtx[0][3]);
	GDWrite_f32(mtx[1][0]);
	GDWrite_f32(mtx[1][1]);
	GDWrite_f32(mtx[1][2]);
	GDWrite_f32(mtx[1][3]);
	if (type == 0) {
		GDWrite_f32(mtx[2][0]);
		GDWrite_f32(mtx[2][1]);
		GDWrite_f32(mtx[2][2]);
		GDWrite_f32(mtx[2][3]);
	}
}

void GDLoadTexMtxIndx(u16 mtx_indx, u32 id, GXTexMtxType type)
{
	u16 addr;
	u8 count;

	if (id >= 0x40) {
		ASSERTMSGLINE(221, type == 0,
			"GDLoadTexMtxIndx: invalid matrix type");

		addr = ((id - 0x40U & 0xffffffff) << 2) + 0x500;
		count = 12;
	} else {
		addr = 4 * id;
		count = type == 1 ? 8 : 12;
	}

  GDWriteXFIndxCCmd(addr, count, mtx_indx);
}

void GDSetCurrentMtx(u32 pn, u32 t0, u32 t1, u32 t2, u32 t3, u32 t4, u32 t5,
                     u32 t6, u32 t7)
{
	u32 regA;
	u32 regB;

	regA = pn << 0
		| t0 << 6
		| t1 << 12
		| t2 << 18
		| t3 << 24;

	regB = t4 << 0
	  | t5 << 6
	  | t6 << 12
	  | t7 << 18;

	GDWriteCPCmd(0x30, regA);
	GDWriteCPCmd(0x40, regB);
	GDWriteXFCmdHdr(0x1018, 2);
	GDWrite_u32(regA);
	GDWrite_u32(regB);
}
