; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:x-p:32:32-i64:64-f80:32-n8:16:32-a:0:32-S32"
target triple = "i686-pc-windows-msvc19.16.27025"

$sub1 = comdat any

$sub2 = comdat any

@giData = common dso_local global i32 0, align 4

; Function Attrs: noinline nounwind optnone
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @sub1()
  call void @sub2()
  ret i32 0
}

; Function Attrs: noinline nounwind optnone
define linkonce_odr dso_local void @sub1() #0 comdat {
entry:
  %liData = alloca i32, align 4
  store i32 5, i32* %liData, align 4
  store i32 6, i32* @giData, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone
define linkonce_odr dso_local void @sub2() #0 comdat {
entry:
  %liData = alloca i32, align 4
  store i32 7, i32* %liData, align 4
  store i32 8, i32* @giData, align 4
  ret void
}

attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"NumRegisterParameters", i32 0}
!1 = !{i32 1, !"wchar_size", i32 2}
!2 = !{!"clang version 7.0.0 (tags/RELEASE_700/final)"}
