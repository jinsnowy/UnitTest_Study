#include "pch.h"

#include "06_단위_테스트_스타일\AuditManager.h"
#include "06_단위_테스트_스타일\FileSystem.h"
#include "MockFileSystem.h"

TEST(TestAuditManager, 기존_파일_FULL일때_새로운_파일에_레코드_생성) {
	// given
	MockFileSystem fileSystem;
	AuditManager sut(fileSystem, 3, ".");

	ON_CALL(fileSystem, GetFiles("."))
		.WillByDefault(Return(vector<string>{
				"./audit_1.txt",
				"./audit_2.txt"
	}));

	ON_CALL(fileSystem, ReadLines("./audit_2.txt"))
		.WillByDefault(Return(vector<string>{
			"Peter;2019-04-06T16:30:30",
			"Jane;2019-11-11T09:30:00",
			"Jack;2019-08-30T02:00:00"
	}));
		

	EXPECT_CALL(fileSystem, WriteLine("./audit_3.txt", "Alice;2019-04-06T18:00:00"))
		.Times(1);

	// when
	sut.AddRecord("Alice", "2019-04-06T18:00:00");
}