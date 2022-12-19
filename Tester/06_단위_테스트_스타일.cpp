#include "pch.h"

#include "06_����_�׽�Ʈ_��Ÿ��\AuditManager.h"
#include "06_����_�׽�Ʈ_��Ÿ��\FileSystem.h"
#include "06_����_�׽�Ʈ_��Ÿ��\ApplicationService.h"
#include "MockFileSystem.h"

TEST(TestAuditManager, ����_����_������_AUDIT_1_TXT_���Ͽ�_���ڵ�_����) {
	// given
	MockFileSystem fileSystem;
	AuditManager sut(fileSystem, 3, ".");

	ON_CALL(fileSystem, GetFiles("."))
		.WillByDefault(Return(vector<string>{}));

	EXPECT_CALL(fileSystem, WriteLine("./audit_1.txt", "Alice;2019-04-06T18:00:00"))
		.Times(1);

	// when
	sut.AddRecord("Alice", "2019-04-06T18:00:00");
}

TEST(TestAuditManager, ����_����_����Ҷ�_����_���Ͽ�_���ڵ�_����) {
	// given
	MockFileSystem fileSystem;
	AuditManager sut(fileSystem, 3, ".");

	ON_CALL(fileSystem, GetFiles("."))
		.WillByDefault(Return(vector<string>{
		"./audit_1.txt"
	}));

	ON_CALL(fileSystem, ReadLines("./audit_1.txt"))
		.WillByDefault(Return(vector<string>{
		"Peter;2019-04-06T16:30:30",
		"Jane;2019-11-11T09:30:00",
	}));


	EXPECT_CALL(fileSystem, WriteLine("./audit_1.txt", "Alice;2019-04-06T18:00:00"))
		.Times(1);

	// when
	sut.AddRecord("Alice", "2019-04-06T18:00:00");
}

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

TEST(TestAuditManager, ����_����_FULL_�϶�_���ο�_���Ͽ�_���ڵ�_����2) {
	// given
	string dirName = ".";
	AuditManager2 sut = AuditManager2(3);
	vector<FileContent> contents = {
		FileContent("audit_1.txt", {}),
		FileContent("audit_2.txt", {
			"Peter;2019-04-06T16:30:30",
			"Jane;2019-11-11T09:30:00",
			"Jack;2019-08-30T02:00:00"
		})
	};

	// when
	FileUpdate update = sut.AddRecord(contents, "Alice", "2019-04-06T18:00:00");

	// then
	ASSERT_EQ(update.fileName, "audit_3.txt");
	ASSERT_EQ(update.newContent, "Alice;2019-04-06T18:00:00");
}