; ModuleID = 'FuncLib.c'
source_filename = "FuncLib.c"
target datalayout = "e-m:x-p:32:32-i64:64-f80:32-n8:16:32-a:0:32-S32"
target triple = "i686-pc-windows-msvc19.16.27025"

@DevMem = dso_local global <{ i16, i16, i16, i16, i16, [251 x i16] }> <{ i16 1, i16 2, i16 3, i16 4, i16 5, [251 x i16] zeroinitializer }>, align 2
@HSTK = common dso_local global i16 0, align 2

; Function Attrs: noinline nounwind optnone
define dso_local void @InstSTMLD(i32 %DevAdr) #0 {
entry:
  %DevAdr.addr = alloca i32, align 4
  store i32 %DevAdr, i32* %DevAdr.addr, align 4
  %0 = load i32, i32* %DevAdr.addr, align 4
  %arrayidx = getelementptr inbounds [256 x i16], [256 x i16]* bitcast (<{ i16, i16, i16, i16, i16, [251 x i16] }>* @DevMem to [256 x i16]*), i32 0, i32 %0
  %1 = load i16, i16* %arrayidx, align 2
  store i16 %1, i16* @HSTK, align 2
  ret void
}

; Function Attrs: noinline nounwind optnone
define dso_local void @InstSTOUT(i32 %DevAdr) #0 {
entry:
  %DevAdr.addr = alloca i32, align 4
  store i32 %DevAdr, i32* %DevAdr.addr, align 4
  %0 = load i16, i16* @HSTK, align 2
  %1 = load i32, i32* %DevAdr.addr, align 4
  %arrayidx = getelementptr inbounds [256 x i16], [256 x i16]* bitcast (<{ i16, i16, i16, i16, i16, [251 x i16] }>* @DevMem to [256 x i16]*), i32 0, i32 %1
  store i16 %0, i16* %arrayidx, align 2
  ret void
}

attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"NumRegisterParameters", i32 0}
!1 = !{i32 1, !"wchar_size", i32 2}
!2 = !{!"clang version 7.0.0 (tags/RELEASE_700/final)"}
