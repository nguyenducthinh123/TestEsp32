﻿#pragma once
#include "Array.h"

class ByteTable : Array<int> {
	int row_size;

public:
	int RowSize() const { return row_size; }
	int Rows() const { return Length(); }
	char* GetRow(int index) { return (char*)GetAt(index); }

public:
	ByteTable& Create(int rows, int cols) {
		return Create(rows, cols, new byte[rows * cols]);
	}

	ByteTable& Create(int rows, int cols, void* data) {
		Resize(rows);

		row_size = cols; // độ rộng bảng (màn hình)
		unsigned p = (unsigned)data;
		for (int i = 0; i < rows; i++, p += cols) { // p += cols là xuống dòng
			SetAt(i, p);
		}
		return *this;
	}
};