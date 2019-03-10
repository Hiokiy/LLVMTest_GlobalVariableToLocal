; ModuleID = 'hoge2.cpp'
source_filename = "hoge2.cpp"
target datalayout = "e-m:x-p:32:32-i64:64-f80:32-n8:16:32-a:0:32-S32"
target triple = "i686-pc-windows-msvc19.16.27025"

; Function Attrs: noinline nounwind optnone
define dso_local i32 @"?test@@YAHHH@Z"(i32 %i, i32 %j) #0 {
entry:
  %j.addr = alloca i32, align 4
  %i.addr = alloca i32, align 4
  %k = alloca i32, align 4
  store i32 %j, i32* %j.addr, align 4
  store i32 %i, i32* %i.addr, align 4
  %0 = load i32, i32* %j.addr, align 4
  %cmp = icmp sgt i32 %0, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %i.addr, align 4
  %2 = load i32, i32* %j.addr, align 4
  %add = add nsw i32 %1, %2
  store i32 %add, i32* %k, align 4
  br label %if.end

if.else:                                          ; preds = %entry
  %3 = load i32, i32* %i.addr, align 4
  %4 = load i32, i32* %j.addr, align 4
  %sub = sub nsw i32 %3, %4
  store i32 %sub, i32* %k, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %5 = load i32, i32* %k, align 4
  %mul = mul nsw i32 %5, 10
  store i32 %mul, i32* %k, align 4
  ret i32 0
}

;attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"NumRegisterParameters", i32 0}
!1 = !{i32 1, !"wchar_size", i32 2}
!2 = !{!"clang version 7.0.0 (tags/RELEASE_700/final)"}
