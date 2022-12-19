#include "pch.h"

#include "06_����_�׽�Ʈ_��Ÿ��\AuditManager.h"
#include "06_����_�׽�Ʈ_��Ÿ��\FileSystem.h"
#include "MockFileSystem.h"

TEST(TestAuditManager, ����_����_FULL�϶�_���ο�_���Ͽ�_���ڵ�_����) {
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