set_project("ZXRenderer")
set_version("1.0.0")
add_defines("ZXRENDEER_VERSION=\"1.0.0\"")

add_rules("mode.debug", "mode.release")
add_repositories("remote-repo https://github.com/ZXPrism/my-xmake-repo.git")
add_requires("sol2", "libsdl3")
add_requires("zxmath")

target("ZXRenderer")
    set_languages("cxx23")
    set_kind("binary")
    set_warnings("all", "error")

    add_packages("sol2", "libsdl3")
    add_packages("zxmath")
    add_files("src/**.cpp")
    add_includedirs("src")

    after_build(function (target)
        os.cp(target:targetfile(), "bin/")
    end)
target_end()

function AddTarget_Demo(demo_name)
    target(demo_name)
        set_languages("cxx23")
        set_kind("binary")
        set_warnings("all", "error")

        add_packages("sol2", "libsdl3")
        add_packages("zxmath")
        add_files("demo/" .. demo_name .. "/**.cpp")
        add_includedirs("demo/" .. demo_name .. "/")

        after_build(function (target)
            os.cp(target:targetfile(), "bin/" .. "demo/" .. demo_name .. "/")
        end)
    target_end()
end
