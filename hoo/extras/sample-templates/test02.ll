; ModuleID = 'test02.cpp'
source_filename = "test02.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind optnone mustprogress
define dso_local i64 @_Z3subll(i64 %a, i64 %b) #0 {
entry:
  %a.addr = alloca i64, align 8
  %b.addr = alloca i64, align 8
  store i64 %a, i64* %a.addr, align 8
  store i64 %b, i64* %b.addr, align 8
  %0 = load i64, i64* %a.addr, align 8
  %1 = load i64, i64* %b.addr, align 8
  %sub = sub nsw i64 %0, %1
  ret i64 %sub
}

; Function Attrs: noinline nounwind optnone mustprogress
define dso_local i64 @_Z9TEST04SUBld(i64 %a, double %b) #0 {
entry:
  %a.addr = alloca i64, align 8
  %b.addr = alloca double, align 8
  store i64 %a, i64* %a.addr, align 8
  store double %b, double* %b.addr, align 8
  %0 = load i64, i64* %a.addr, align 8
  %conv = sitofp i64 %0 to double
  %1 = load double, double* %b.addr, align 8
  %sub = fsub double %conv, %1
  %conv1 = fptosi double %sub to i64
  ret i64 %conv1
}

attributes #0 = { noinline nounwind optnone mustprogress "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-features"="+cx8,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 12.0.1"}
