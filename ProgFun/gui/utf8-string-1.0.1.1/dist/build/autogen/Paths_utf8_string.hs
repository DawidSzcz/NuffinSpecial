module Paths_utf8_string (
    version,
    getBinDir, getLibDir, getDataDir, getLibexecDir,
    getDataFileName
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
catchIO = Exception.catch


version :: Version
version = Version {versionBranch = [1,0,1,1], versionTags = []}
bindir, libdir, datadir, libexecdir :: FilePath

bindir     = "/home/kazek/.cabal/bin"
libdir     = "/home/kazek/.cabal/lib/utf8-string-1.0.1.1/ghc-7.6.3"
datadir    = "/home/kazek/.cabal/share/utf8-string-1.0.1.1"
libexecdir = "/home/kazek/.cabal/libexec"

getBinDir, getLibDir, getDataDir, getLibexecDir :: IO FilePath
getBinDir = catchIO (getEnv "utf8_string_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "utf8_string_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "utf8_string_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "utf8_string_libexecdir") (\_ -> return libexecdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
