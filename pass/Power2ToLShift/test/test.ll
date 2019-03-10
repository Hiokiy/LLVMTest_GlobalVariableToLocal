; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:x-p:32:32-i64:64-f80:32-n8:16:32-a:0:32-S32"
target triple = "i686-pc-windows-msvc19.16.27025"

; Function Attrs: noinline nounwind optnone
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  ret i32 0
}

; Function Attrs: noinline nounwind optnone
define dso_local i32 @test_multByPwr2_leftSide() #0 {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  store i32 0, i32* %a, align 4
  store i32 3, i32* %b, align 4
  %0 = load i32, i32* %b, align 4
  %mul = mul nsw i32 128, %0
  store i32 %mul, i32* %a, align 4
  ret i32 %mul
}

; Function Attrs: noinline nounwind optnone
define dso_local i32 @test_multByPwr2_rightSide() #0 {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  store i32 0, i32* %a, align 4
  store i32 3, i32* %b, align 4
  %0 = load i32, i32* %b, align 4
  %mul = mul nsw i32 %0, 1024
  store i32 %mul, i32* %a, align 4
  ret i32 %mul
}

; Function Attrs: noinline nounwind optnone
define dso_local i32 @test_multByOtherValue_leftSide() #0 {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  store i32 0, i32* %a, align 4
  store i32 3, i32* %b, align 4
  %0 = load i32, i32* %b, align 4
  %mul = mul nsw i32 129, %0
  store i32 %mul, i32* %a, align 4
  ret i32 %mul
}

; Function Attrs: noinline nounwind optnone
define dso_local i32 @test_multByOtherValue_rightSide() #0 {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  store i32 0, i32* %a, align 4
  store i32 3, i32* %b, align 4
  %0 = load i32, i32* %b, align 4
  %mul = mul nsw i32 %0, 1023
  store i32 %mul, i32* %a, align 4
  ret i32 %mul
}

;attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"NumRegisterParameters", i32 0}
!1 = !{i32 1, !"wchar_size", i32 2}
!2 = !{!"clang version 7.0.0 (tags/RELEASE_700/final)"}
