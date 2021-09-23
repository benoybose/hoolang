; ModuleID = 'test01.cpp'
source_filename = "test01.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone mustprogress
define dso_local i64 @_Z5add_1ll(i64 %a, i64 %b) #0 {
entry:
  %a.addr = alloca i64, align 8
  %b.addr = alloca i64, align 8
  store i64 %a, i64* %a.addr, align 8
  store i64 %b, i64* %b.addr, align 8
  %0 = load i64, i64* %a.addr, align 8
  %1 = load i64, i64* %b.addr, align 8
  %add = add nsw i64 %0, %1
  ret i64 %add
}

; Function Attrs: noinline nounwind optnone mustprogress
define dso_local i64 @_Z5add_2mm(i64 %a, i64 %b) #0 {
entry:
  %a.addr = alloca i64, align 8
  %b.addr = alloca i64, align 8
  store i64 %a, i64* %a.addr, align 8
  store i64 %b, i64* %b.addr, align 8
  %0 = load i64, i64* %a.addr, align 8
  %1 = load i64, i64* %b.addr, align 8
  %add = add i64 %0, %1
  ret i64 %add
}

; Function Attrs: noinline nounwind optnone mustprogress
define dso_local zeroext i8 @_Z5add_3hh(i8 zeroext %a, i8 zeroext %b) #0 {
entry:
  %a.addr = alloca i8, align 1
  %b.addr = alloca i8, align 1
  store i8 %a, i8* %a.addr, align 1
  store i8 %b, i8* %b.addr, align 1
  %0 = load i8, i8* %a.addr, align 1
  %conv = zext i8 %0 to i32
  %1 = load i8, i8* %b.addr, align 1
  %conv1 = zext i8 %1 to i32
  %add = add nsw i32 %conv, %conv1
  %conv2 = trunc i32 %add to i8
  ret i8 %conv2
}

; Function Attrs: noinline nounwind optnone mustprogress
define dso_local void @_Z4testv() #0 {
entry:
  %call = call i64 @_Z5add_1ll(i64 3, i64 4)
  %call1 = call i64 @_Z5add_2mm(i64 3, i64 4)
  %call2 = call zeroext i8 @_Z5add_3hh(i8 zeroext 3, i8 zeroext 4)
  ret void
}

attributes #0 = { noinline nounwind optnone mustprogress "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features"="+cx8,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 12.0.1"}
